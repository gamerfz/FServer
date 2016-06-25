#pragma once
#include <Singleton.h>
#include <NetInterface.h>
#include "ClientMsg.pb.h"
#include "ServerMsg.pb.h"

#define theProtoMsgMgr ProtoMessage::GetInstance()
class ProtoMessage : public Singleton<ProtoMessage>
{
public:
	ProtoMessage();
	~ProtoMessage();

	MsgType GetMsgType(const NetMessage* msg);
};

/*ÏûÏ¢½âÎö*/
template< class Message >
bool MsgFromBytes(const NetMessage* nmsg, Message& msg)
{
	if (!msg.ParseFromArray(nmsg->mMsg, nmsg->mLength))
		return false;
	return true;
}

#define MESSAGE_HANDLE(MsgID, MsgName, MsgHandle)				\
	case MsgID:													\
		{														\
			MsgName msg;										\
			if (MsgFromBytes(nmsg, msg))						\
				MsgHandle(&msg);								\
			else												\
				LOG(ERROR) << "Message handle error!";			\
		}														\
		break;

