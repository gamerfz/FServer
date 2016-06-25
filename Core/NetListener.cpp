#include "NetListener.h"
#include <thread>
#include "NetWork.h"
#include "NetDefine.h"

NetListener::NetListener()
{
	mEvBase = NULL;
	mListener = NULL;
}

NetListener::~NetListener()
{
	StopListen();
}

bool NetListener::StartListen(NetWork* net)
{
#ifndef WIN32
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, 0);
#endif
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(net->GetPort());

	LOG(INFO) << "Server listen with " << net->GetPort();

	//简单创建,不建议使用event_config,用处不大
	mEvBase = event_base_new();
	if (!mEvBase)
		return false;

	mListener = evconnlistener_new_bind(mEvBase, listener_cb, (void*)net, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin, sizeof(sin));

	if (!mListener)
	{
		LOG(ERROR) << "Create listener failed";
		StopListen();
		return false;
	}
	std::thread(event_base_loop, mEvBase, 0).detach();

	LOG(INFO) << "Create listener successful";
	return true;
}

bool NetListener::StopListen()
{
	if (mListener)
	{
		evconnlistener_free(mListener);
		mListener = NULL;
	}
	if (mEvBase)
	{
		event_base_free(mEvBase);
		mEvBase = NULL;
	}
	LOG(INFO) << "Server stop listening";
	return true;
}

void NetListener::listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* uData)
{
	LOG(INFO) << "Listen to fd:" << fd 
		<< " IP:" << inet_ntoa(((sockaddr_in *)sock)->sin_addr) << " Port:" << ((sockaddr_in *)sock)->sin_port 
		<< " len:" << socklen;
	NetWork* net = (NetWork*)uData;
	if (net->RemoveNetObject(fd))//有就删掉老的出log,没有继续
		LOG(INFO) << "Repeated socket " << fd;

	if (net->CheckConnectFull())
	{
		LOG(ERROR) << "Network is full!";//并T掉
		return;
	}

	auto it = net->DispatchIO();
	if (!it)
	{
		//log
		return;
	}
	if (!it->IsValid())
	{
		//log
		return;
	}
	auto conn = new NetConnect;
	conn->mFD = fd;
	conn->mIP = ((sockaddr_in *)sock)->sin_addr.s_addr;
	conn->mPort = ((sockaddr_in *)sock)->sin_port;
	conn->mAddr = *(sockaddr_in*)sock;
	conn->mCaller = false;
	it->GetConnectQueue()->PushToQueue(conn);
}
