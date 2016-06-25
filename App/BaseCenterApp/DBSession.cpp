#include "DBSession.h"
#include "BaseCenterApp.h"
#include "ConfigManager.h"
#include "ProtoMessage.h"

void DBSession::Connected()
{
	LOG(INFO) << "DBMgr connected!";
	MsgRegisterApp msg;
	msg.mutable_base()->set_type(Msg_RegisterApp);
	msg.set_app_type(ESAT_BaseCenter);
	msg.set_app_id(theConfigMgr->GetAppID());
	SendToDB(&msg);
}

void DBSession::Disconnected()
{
	if (GetSStatus() == ESSS_Connected)
		LOG(INFO) << "DBMgrApp disconnected!";
	else
		LOG(INFO) << "DBMgrApp connect failed!";
	ServerSession::Disconnected();
}

bool DBSession::SendToDB(::google::protobuf::Message* pbMsg)
{
	return theBaseCenterApp->GetNetLogic()->OnSend(this, pbMsg);
}

void DBSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}