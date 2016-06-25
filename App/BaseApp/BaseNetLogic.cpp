#include "BaseNetLogic.h"
#include "ProtoMessage.h"

BaseNetLogic::BaseNetLogic()
{
}

BaseNetLogic::~BaseNetLogic()
{
}

void BaseNetLogic::OnMessage(const NetPacket& packet)
{
	NetMessage* nmsg = (NetMessage*)(packet.mBody);

	auto msgType = theProtoMsgMgr->GetMsgType(nmsg);
#ifdef DEBUG
	LOG(INFO) << "msg " << msgType;
#endif
	switch (msgType)
	{
	default:
		NetInterface::OnMessage(packet, msgType);
		break;
	}
}