#include "App.h"

App::App()
{
}

App::~App()
{
}

bool App::SendToApp(::google::protobuf::Message* pbMsg)
{
	return theDBMgrApp->GetNetLogic()->OnSend(this, pbMsg);
}

void App::Connected()
{
	LOG(INFO) << "App connected!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID());
}

void App::Disconnected()
{
	LOG(INFO) << "App disconnected!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID());
}

void App::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (GetAppType())
	{
	case ESAT_BaseCenter:
		OnBCMsg(nmsg, msgType);
		break;
	case ESAT_Base:
		OnBaseMsg(nmsg, msgType);
		break;
	case ESAT_Login:
		OnLoginMsg(nmsg, msgType);
		break;
	default:
		LOG(ERROR) << "Unknown App msg!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID()) << LogValue("msgtype", msgType);
		break;
	}
}

void App::OnBCMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (msgType)
	{
		/*		MESSAGE_HANDLE(Msg_RespondApp, MsgRespondApp, OnMsgRespondApp)
		/*		MESSAGE_HANDLE(Msg_RespondApp+1, MsgRespondApp, OnMsgRespondApp)*/
	default:
		LOG(INFO) << "Unknown msg!" << LogValue("msgType", msgType);
		break;
	};
}
void App::OnBaseMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
void App::OnLoginMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}