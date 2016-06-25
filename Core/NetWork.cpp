#include "NetWork.h"

bool NetWork::CreateNet()
{
	if (mIOCount <= 0)
		return false;

#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	mEvBase = event_base_new();
	if (!mEvBase)
		return false;

	mListener = new NetListener;
	if (!mListener->StartListen(this))
	{
		CloseNet();
		return false;
	}

	for (int i = 0; i < mIOCount; ++i)
	{
		auto ioThd = new NetIO;
		ioThd->Init(this, i);
		ioThd->Run();
		mvecNetIO.push_back(ioThd);
	}
	if (!mvecNetIO.size())
	{
		CloseNet();
		return false;
	}
	mCurIOIndex = 0;

	return true;
}

bool NetWork::StartNet()
{
	if (event_base_loop(mEvBase, 0) < 0)//0表示成功，-1表示发生了错误，1表示没有事件被注册。服务器正常启动后会循环等事件触发
		return false;
	return true;
}

bool NetWork::CloseNet()
{
	/*注意销毁的顺序,所有event_base在各自的类中都是最后free的*/
	if (mListener)
	{
		delete mListener;
		mListener = NULL;
	}
	for (auto it = mmapObject.begin(); it != mmapObject.end(); it++)
	{
		bufferevent_free(it->second->GetEvBuf());
		evutil_closesocket(it->first);
		delete it->second;
		it->second = NULL;
	}
	mmapObject.clear();

	for (int i = 0; i < mvecNetIO.size(); ++i)
	{
		auto it = mvecNetIO[i];
		it->Stop();
		delete it;
		it = NULL;
	}
	mvecNetIO.clear();

	if (mEvBase)
	{
		event_base_free(mEvBase);
		mEvBase = NULL;
	}
#ifdef WIN32
	WSACleanup();
#endif
	LOG(INFO) << "Network close!";
	return true;
}

evutil_socket_t NetWork::ConnectTo(const std::string& ip, int port)
{
	auto it = DispatchIO();
	if (!it)
	{
		LOG(ERROR) << "NetIO not initialized! Plase CreateNet!";
		return -1;
	}

	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());//如有需要也可以改写使用扩展inet_pton(AF_INET, ip.c_str(), &sin.sin_addr) AF_INET6
	sin.sin_port = htons(port);

	auto evBuf = bufferevent_socket_new(it->GetEvBase(), -1, BEV_OPT_CLOSE_ON_FREE);
	if (!evBuf)
		return -1;
	
	if (bufferevent_socket_connect(evBuf, (sockaddr*)&sin, sizeof(sin)) < 0)
	{
		bufferevent_free(evBuf);
		evBuf = NULL;
		return -1;
	}

	auto fd = bufferevent_getfd(evBuf);//bufferevent_socket_connect后生成fd
	auto obj = new NetObject(this, fd, evBuf, it->GetTID());
	if (!AddNetObject(fd, obj))
	{
		delete obj;
		obj = NULL;
		return -1;
	}
	bufferevent_setcb(obj->GetEvBuf(), conn_readcb, conn_writecb, conn_eventcb, obj);

	auto conn = new NetConnect;
	conn->mFD = fd;
	conn->mIP = sin.sin_addr.s_addr;
	conn->mPort = sin.sin_port;
	conn->mAddr = sin;
	conn->mCaller = true;
	it->GetConnectQueue()->PushToQueue(conn);
	return fd;
}

void NetWork::OnConnectEvent(void* msg, void* args)
{
	auto conn = (NetConnect*)msg;
	auto io = (NetIO*)args;
	if (conn && io)
	{
		if (!conn->mCaller)
		{
			auto evBuf = bufferevent_socket_new(io->GetEvBase(), conn->mFD, BEV_OPT_CLOSE_ON_FREE);
			if (evBuf)
			{
				auto obj = new NetObject(this, conn->mFD, evBuf, io->GetTID());
				if (obj)
				{
					bufferevent_setcb(evBuf, conn_readcb, conn_writecb, conn_eventcb, obj);
					bufferevent_enable(evBuf, EV_READ | EV_WRITE);
					bufferevent_setwatermark(evBuf, EV_READ, 0, 64 * 1024);
					if (!AddNetObject(conn->mFD, obj))
					{
						delete obj;
						obj = NULL;
						return;
					}
					obj->SetConnected(true);
					/*心跳机制 设置监听连接读事件的超时,回调conn_eventcb*/
					struct timeval tv;
					tv.tv_sec = NET_TIMEOUT_SECONDS * 2;
					tv.tv_usec = 0;
					bufferevent_set_timeouts(evBuf, &tv, NULL);
				}
			}
		}
// 		else
// 		{
// 			auto obj = GetNetObject(conn->mFD);
// 			if (obj)
// 			{
// 				/*主动请求(本地Client)的连接只要知道断开或错误,暂时不需要超时机制*/
// 				struct timeval tv;
// 				tv.tv_sec = NET_TIMEOUT_SECONDS;
// 				tv.tv_usec = 0;
// 				bufferevent_set_timeouts(obj->GetEvBuf(), &tv, NULL);
// 			}
// 		}
		delete conn;
		conn = NULL;
	}
}

void NetWork::OnInputEvent(void* msg, void* args)
{
	auto packet = (NetPacket*)msg;
	auto io = (NetIO*)args;
	/*NetMessage* rmsg = (NetMessage*)packet->mBody;*/
	if (mOnNetCB(*packet))//回调上层处理函数
	{
		;
	}
	if (packet->mEvent == ENPE_Read)
		delete[] msg;
	else
		delete msg;
}

void NetWork::OnOutputEvent(void* msg, void* args)
{
	auto packet = (NetPacket*)msg;
	auto io = (NetIO*)args;
	NetMessage* rmsg = (NetMessage*)packet->mBody;
	if (packet->mFD >= 0)
		Send(packet->mBody, rmsg->mLength, packet->mFD);
	if (packet->mEvent == ENPE_Write || packet->mEvent == ENPE_Broadcast)
		delete[] msg;
	else
		delete msg;
}

bool NetWork::SendData(NetPacket* packet)
{
	if (packet->mEvent == ENPE_Broadcast)
	{
		/*广播的消息直接发送,也可以随便找个IO线程加进队列*/
		NetMessage* msg = (NetMessage*)packet->mBody;
		SendToAll(packet->mBody, msg->mLength);
// 		if (mvecNetIO.size())
// 			mvecNetIO[0]->GetOutputQueue()->PushToQueue(packet);

		delete[] msg;
		return true;
	}
	else
	{
		auto obj = mmapObject.find(packet->mFD);
		if (obj != mmapObject.end())
		{
			auto io = GetNetIO(obj->second->GetTID());
			if (io)
			{
				io->GetOutputQueue()->PushToQueue(packet);
				return true;
			}
		}
		delete[] packet;
	}
	return false;
}

bool NetWork::RemoveNetObject(const int fd)
{
	auto it = mmapObject.find(fd);
	if (it == mmapObject.end())
		return false;
	bufferevent_free(it->second->GetEvBuf());
	evutil_closesocket(it->first);
	delete it->second;
	it->second = NULL;
	mmapObject.erase(it);
	return true;
}

bool NetWork::SetEvBufferTimeout(int fd, int sec)
{
	auto obj = GetNetObject(fd);
	if (!obj)
		return false;
	struct timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = 0;
	bufferevent_set_timeouts(obj->GetEvBuf(), &tv, NULL);
	return true;
}

NetIO* NetWork::DispatchIO()
{
	if (!mvecNetIO.size())
		return NULL;
	if (mCurIOIndex >= mvecNetIO.size())
		mCurIOIndex = 0;
	int idx = mCurIOIndex;
	mCurIOIndex++;
	return mvecNetIO[idx];
}

NetIO* NetWork::GetNetIO(int tid)
{
	if (tid >= 0 && tid < mvecNetIO.size())
		return mvecNetIO[tid];
	return NULL;
}

NetObject* NetWork::GetNetObject(int fd)
{
	auto it = mmapObject.find(fd);
	if (it != mmapObject.end())
		return it->second;
	return NULL;
}

bool NetWork::Send(const char* msg, const int len, const int fd)
{
	if (len <= 0)
		return false;
	auto it = mmapObject.find(fd);
	if (it == mmapObject.end())
		return false;
	auto evBuf = it->second->GetEvBuf();
	if (evBuf == NULL)
		return false;
	return (bufferevent_write(evBuf, msg, len) == 0);//return 0 if successful, or -1 if an error occurred
}

bool NetWork::SendToAll(const char* msg, const int len)
{
	if (len <= 0)
		return false;
	bufferevent* evBuf = NULL;
	for (auto it = mmapObject.begin(); it != mmapObject.end(); ++it)
	{
		evBuf = it->second->GetEvBuf();
		if (evBuf != NULL)
			bufferevent_write(evBuf, msg, len);
	}
	return true;
}

void NetWork::conn_readcb(bufferevent* evBuf, void* uData)
{
	auto obj = (NetObject*)uData;
	if (!obj)
		return;
	auto io = obj->GetNetWork()->GetNetIO(obj->GetTID());
	if (!io)
		return;
	evbuffer* input = bufferevent_get_input(evBuf);
	if (!input)
		return;
	size_t len = evbuffer_get_length(input);
	int head;//包头 消息体的长度
	if (evbuffer_copyout(input, &head, MSG_HEAD_LENGTH) != MSG_HEAD_LENGTH)
		return;//取消息头错误
	if (head > MSG_MAX_LENGTH)//出现这种情况建议拆包
	{
		LOG(ERROR) << "Msg is too big!" << LogValue("fd", obj->GetFD()) << LogValue("len", head);
		return;
	}
	size_t msgSize = head;
	if (msgSize > len)
		return;//未收全,大小不够,等下次收全

	/*LOG(INFO) << "head " << head;*/
	//网络包里面需要的内容,接收到的带消息头的完整消息体
	auto strPacket = new char[NET_PACKET_BASE_LENGTH + len];//char数组的长度根据NetPacket内实际大小动态new
	NetPacket* packet = (NetPacket*)strPacket;
	packet->mEvent = ENPE_Read;
	packet->mFD = obj->GetFD();
	packet->mIndex = obj->GetIndex();
	if (evbuffer_remove(input, &packet->mBody, msgSize) > 0)
		io->GetInputQueue()->PushToQueue(packet);//添加到接收消息的事件队列
	else
		delete[] strPacket;
}
void NetWork::conn_writecb(bufferevent* evBuf, void* uData)
{
	//见Send或SendToAll
}
void NetWork::conn_eventcb(bufferevent* evBuf, short events, void* uData)
{
	auto obj = (NetObject*)uData;
	if (!obj)
		return;
	auto net = obj->GetNetWork();
	if (!net)
		return;
	auto io = net->GetNetIO(obj->GetTID());
	if (!io)
		return;
	if (events & BEV_EVENT_CONNECTED)
	{
		/*注意,这里连接成功只针对本地主动请求的连接,监听的连接见OnConnectEvent*/
		bufferevent_enable(obj->GetEvBuf(), EV_READ | EV_WRITE);
		bufferevent_setwatermark(obj->GetEvBuf(), EV_READ, 0, 64 * 1024);
		obj->SetConnected(true);
		auto packet = new NetPacket;
		packet->mEvent = ENPE_Connected;
		packet->mFD = obj->GetFD();
		packet->mIndex = obj->GetIndex();
		io->GetInputQueue()->PushToQueue(packet);
	}
	else if (events & BEV_EVENT_EOF || events & BEV_EVENT_ERROR)
	{
		obj->SetConnected(false);
		auto packet = new NetPacket;
		packet->mEvent = ENPE_Disconnect;
		packet->mFD = obj->GetFD();
		packet->mIndex = obj->GetIndex();
		io->GetInputQueue()->PushToQueue(packet);
		net->RemoveNetObject(obj->GetFD());
	}
	else if (events & BEV_EVENT_TIMEOUT)
	{
		/*监听检测的,但默认不处理超时，需要上层自己决定调用SetDetect*/
		if (obj->IsDetect())
		{
			LOG(INFO) << LogValue("bf", obj->GetFD());
			obj->SetConnected(false);
			auto packet = new NetPacket;
			packet->mEvent = ENPE_Disconnect;
			packet->mFD = obj->GetFD();
			packet->mIndex = obj->GetIndex();
			io->GetInputQueue()->PushToQueue(packet);
			net->RemoveNetObject(obj->GetFD());
		}
		else
		{
			//做的好点可以设置一个时间,给上层设置#
			bufferevent_enable(obj->GetEvBuf(), EV_READ | EV_WRITE);//重新读写事件,继续心跳检测
		}
	}
}