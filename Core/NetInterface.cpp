#include "NetInterface.h"

NetInterface::NetInterface():
mNetWork(NULL)
{
}

NetInterface::~NetInterface()
{
}

bool NetInterface::Init(int port, int connCnt, int ioCnt /* = 4 */)
{
	mNetWork = new NetWork(this, &NetInterface::OnNetEvent, port, connCnt, ioCnt);
	if (!mNetWork->CreateNet())
		return false;
	mvecSession.resize(mNetWork->GetMaxConnect());
	return true;
}

evutil_socket_t NetInterface::OnConnectTo(const std::string& ip, int port)
{
	if (!mNetWork)
		return -1;
	return mNetWork->ConnectTo(ip, port);
}


void NetInterface::OnMessage(const NetPacket& msg, int msgType /* = 0 */)
{
	auto session = GetSession(msg.mIndex);
	if (session)
		session->OnMsg((NetMessage*)(msg.mBody), msgType);
}

bool NetInterface::OnSend(BaseSession* session, ::google::protobuf::Message* pbMsg)
{
	if (!mNetWork)
		return false;
	auto packet = BuildOutPacket(session, pbMsg);
	if (!packet)
		return false;
	return SendPacket(packet);
}

bool NetInterface::OnSend(int fd, ::google::protobuf::Message* pbMsg)
{
	if (!mNetWork)
		return false;
	auto packet = BuildOutPacket(fd, pbMsg);
	if (!packet)
		return false;
	return SendPacket(packet);
}

bool NetInterface::OnSendToAll(::google::protobuf::Message* pbMsg)
{
	if (!mNetWork)
		return false;
	auto packet = BuildBroadcastPacket(pbMsg);
	if (!packet)
		return false;
	return SendPacketToAll(packet);
}

bool NetInterface::OnDisconnect(int index)
{
	if (!mNetWork)
		return false;
	auto session = GetSession(index);
	if (!session)
		return false;
	/*直接删除,如果有需要也可以走底层队列处理session*/
	mNetWork->RemoveNetObject(session->GetFD());
	session->Disconnected();
	RemoveSession(session);
	return true;
}

bool NetInterface::OnDisconnectByFD(int fd)
{
	if (!mNetWork)
		return false;
	auto session = GetSessionByFD(fd);
	if (!session)
		return false;
	mNetWork->RemoveNetObject(session->GetFD());
	session->Disconnected();
	RemoveSession(session);
	return true;
}

bool NetInterface::AttachSession(BaseSession* session)
{
	if (session->GetIndex() != -1)//重复检测
		return false;
	if (session->GetFD() == -1)
	{
		for (int i = 0; i < mvecSession.size(); ++i)
		{
			if (mvecSession[i] == NULL)
			{
				session->SetIndex(i);
				mvecSession[i] = session;
				return true;
			}
		}
	}
	else if (!GetSessionByFD(session->GetFD()))
	{
		auto it = GetNetObject(session);
		if (!it)
			return false;
		for (int i = 0; i < mvecSession.size(); ++i)
		{
			if (mvecSession[i] == NULL)
			{
				session->SetIndex(i);
				it->SetIndex(i);
				mvecSession[i] = session;
				return true;
			}
		}
	}

	return false;
}

void NetInterface::RemoveSession(BaseSession* session)
{
	if (GetSession(session->GetIndex()))
	{
		if (session == mvecSession[session->GetIndex()])
		{
			mvecSession[session->GetIndex()] = NULL;
			session->SetFD(-1);
			session->SetIndex(-1);
		}
	}
}

NetObject* NetInterface::GetNetObject(BaseSession* session)
{
	return mNetWork->GetNetObject(session->GetFD());
}

BaseSession* NetInterface::GetSession(int index)
{
	if (index >= 0 && index < mvecSession.size())
		return mvecSession[index];
	return NULL;
}

BaseSession* NetInterface::GetSessionByFD(int fd)
{
	for (int i = 0; i < mvecSession.size(); i++)
	{
		if (mvecSession[i])
		{
			if (mvecSession[i]->GetFD() == fd)
				return mvecSession[i];
		}
	}
	return NULL;
}

int NetInterface::OnNetEvent(const NetPacket& msg)
{
	switch (msg.mEvent)
	{
	case ENPE_Connected:
		{
			auto session = GetSession(msg.mIndex);
			if (session)
				session->Connected();
			else
				OnConnected(msg);
		}
		break;
	case ENPE_Disconnect:
		{
			auto session = GetSession(msg.mIndex);
			if (session)
			{
				session->Disconnected();
				RemoveSession(session);
			}
		}
		break;
	case ENPE_Read:
		{
			/*消息处理分发*/
			OnMessage(msg);
		}
		break;
	default:
		break;
	}
	return 0;
}

NetPacket* NetInterface::BuildOutPacket(BaseSession* session, ::google::protobuf::Message* pbMsg)
{
	if (session->GetIndex() < 0 || session->GetIndex() >= mvecSession.size())
		return NULL;
	NetMessage* message = NULL;
	char* strPacket = new char[NET_PACKET_BASE_LENGTH + MSG_HEAD_LENGTH + pbMsg->ByteSize()];
	NetPacket* packet = (NetPacket*)strPacket;
	packet->mEvent = ENPE_Write;
	packet->mFD = session->GetFD();
	packet->mIndex = session->GetIndex();
	message = (NetMessage*)packet->mBody;
	message->mLength = pbMsg->ByteSize() + MSG_HEAD_LENGTH;
	pbMsg->SerializeToArray(message->mMsg, pbMsg->ByteSize());
	return packet;
}

NetPacket* NetInterface::BuildOutPacket(int fd, ::google::protobuf::Message* pbMsg)
{
	auto obj = GetNetWork()->GetNetObject(fd);
	if (!obj)
		return NULL;
	NetMessage* message = NULL;
	char* strPacket = new char[NET_PACKET_BASE_LENGTH + MSG_HEAD_LENGTH + pbMsg->ByteSize()];
	NetPacket* packet = (NetPacket*)strPacket;
	packet->mEvent = ENPE_Write;
	packet->mFD = obj->GetFD();
	packet->mIndex = obj->GetIndex();
	message = (NetMessage*)packet->mBody;
	message->mLength = pbMsg->ByteSize() + MSG_HEAD_LENGTH;
	pbMsg->SerializeToArray(message->mMsg, pbMsg->ByteSize());
	return packet;
}

NetPacket* NetInterface::BuildBroadcastPacket(::google::protobuf::Message* pbMsg)
{
	NetMessage* message = NULL;
	char* strPacket = new char[NET_PACKET_BASE_LENGTH + MSG_HEAD_LENGTH + pbMsg->ByteSize()];
	NetPacket* packet = (NetPacket*)strPacket;
	packet->mEvent = ENPE_Broadcast;
	packet->mFD = -1;
	packet->mIndex = -1;
	message = (NetMessage*)packet->mBody;
	message->mLength = pbMsg->ByteSize() + MSG_HEAD_LENGTH;
	pbMsg->SerializeToArray(message->mMsg, pbMsg->ByteSize());
	return packet;
}

bool NetInterface::SendPacket(NetPacket* packet)
{
	return mNetWork->SendData(packet);
}

bool NetInterface::SendPacketToAll(NetPacket* packet)
{
	return mNetWork->SendData(packet);
}
