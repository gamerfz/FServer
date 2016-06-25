#include "GCSession.h"
#include "CubbyApp.h"
#include "ConfigManager.h"
#include "ProtoMessage.h"

void GCSession::Connected()
{
	LOG(INFO) << "GameCenterApp connected!";
	MsgRegisterApp msg;
	msg.mutable_base()->set_type(Msg_RegisterApp);
	msg.set_app_type(ESAT_Cubby);
	msg.set_app_id(theConfigMgr->GetAppID());
	SendToGC(&msg);
}

void GCSession::Disconnected()
{
	if (GetSStatus() == ESSS_Connected)
		LOG(INFO) << "GameCenterApp disconnected!";
	else
		LOG(INFO) << "GameCenterApp connect failed!";
	ServerSession::Disconnected();
}

bool GCSession::SendToGC(::google::protobuf::Message* pbMsg)
{
	return theCubbyApp->GetNetLogic()->OnSend(this, pbMsg);
}

void GCSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}