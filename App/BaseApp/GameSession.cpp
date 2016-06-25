#include "GameSession.h"
#include "BaseApp.h"
#include "ConfigManager.h"
#include "ProtoMessage.h"

void GameSession::Connected()
{
	LOG(INFO) << "GameApp connected!";
	MsgRegisterApp msg;
	msg.mutable_base()->set_type(Msg_RegisterApp);
	msg.set_app_type(ESAT_Base);
	msg.set_app_id(theConfigMgr->GetAppID());
	SendToGame(&msg);
}

void GameSession::Disconnected()
{
	if (GetSStatus() == ESSS_Connected)
		LOG(INFO) << "GameApp disconnected!";
	else
		LOG(INFO) << "GameApp connect failed!";
	ServerSession::Disconnected();
}

bool GameSession::SendToGame(::google::protobuf::Message* pbMsg)
{
	return theBaseApp->GetNetLogic()->OnSend(this, pbMsg);
}

void GameSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
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