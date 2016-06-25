#include "BaseApp.h"

BaseApp::BaseApp()
{
}

BaseApp::~BaseApp()
{
}

bool BaseApp::SendToApp(::google::protobuf::Message* pbMsg)
{
	return theGameApp->GetNetLogic()->OnSend(this, pbMsg);
}

void BaseApp::Connected()
{

}

void BaseApp::Disconnected()
{

}

void BaseApp::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
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
