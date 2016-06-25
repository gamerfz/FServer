#include "BaseApp.h"

BaseApp::BaseApp()
{
}

BaseApp::~BaseApp()
{
}

bool BaseApp::SentToBase(::google::protobuf::Message* pbMsg)
{
	return theDBMgrApp->GetNetLogic()->OnSend(this, pbMsg);
}

void BaseApp::Connected()
{

}

void BaseApp::Disconnected()
{

}

void BaseApp::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
