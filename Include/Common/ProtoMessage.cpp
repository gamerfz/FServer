#include "ProtoMessage.h"

InitSingleton(ProtoMessage)
ProtoMessage::ProtoMessage()
{
}

ProtoMessage::~ProtoMessage()
{
}

MsgType ProtoMessage::GetMsgType(const NetMessage* msg)
{
	MsgParse mParse;
	if (!MsgFromBytes(msg, mParse))
	{
		LOG(ERROR) << "ParseFromArray error!";
		return Msg_Default;
	}
	return mParse.base().type();
}