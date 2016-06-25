#include "BCSession.h"
#include "BaseApp.h"
#include "ConfigManager.h"
#include "ProtoMessage.h"

void BCSession::Connected()
{
	LOG(INFO) << "BaseCenterApp connected!";
	//ÏòBaseCenterApp×¢²á
	MsgRegisterApp msg;
	msg.mutable_base()->set_type(Msg_RegisterApp);
	msg.set_app_type(ESAT_Base);
	msg.set_app_id(theConfigMgr->GetAppID());
	SendToBC(&msg);
}

void BCSession::Disconnected()
{
	if (GetSStatus() == ESSS_Connected)
		LOG(INFO) << "BaseCenterApp disconnected!";
	else
		LOG(INFO) << "BaseCenterApp connect failed!";
	ServerSession::Disconnected();
}

bool BCSession::SendToBC(::google::protobuf::Message* pbMsg)
{
	return theBaseApp->GetNetLogic()->OnSend(this, pbMsg);
}

void BCSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (msgType)
	{
		MESSAGE_HANDLE(Msg_RespondApp, MsgRespondApp, OnMsgRespondApp)
/*		MESSAGE_HANDLE(Msg_RespondApp+1, MsgRespondApp, OnMsgRespondApp)*/
	default:
		LOG(INFO) << "Unknown msg!" << LogValue("msgType", msgType);
		break;
	};
}

void BCSession::OnMsgRespondApp(MsgRespondApp* msg)
{
	if (msg->mutable_base()->has_result())
	{
		msg->base().result();
	}
}