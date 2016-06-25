#include "BCSession.h"
#include "LoginApp.h"
#include "ConfigManager.h"
#include "ProtoMessage.h"

void BCSession::Connected()
{
	LOG(INFO) << "BaseCenterApp connected!";
	MsgRegisterApp msg;
	msg.mutable_base()->set_type(Msg_RegisterApp);
	msg.set_app_type(ESAT_Login);
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
	return theLoginApp->GetNetLogic()->OnSend(this, pbMsg);
}

void BCSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (msgType)
	{
	case Msg_RespondApp:
		{
			MsgRespondApp msg;
			if (!MsgFromBytes(nmsg, msg))
				return;
		}
		break;
	default:
		LOG(INFO) << "Unknown msg!" << LogValue("msgType", msgType);
		break;
	};
}