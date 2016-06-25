#include "BaseCenterApp.h"

BaseCenterApp::BaseCenterApp()
{
}

BaseCenterApp::~BaseCenterApp()
{
}

bool BaseCenterApp::SentToBC(::google::protobuf::Message* pbMsg)
{
	return theDBMgrApp->GetNetLogic()->OnSend(this, pbMsg);
}

void BaseCenterApp::Connected()
{

}

void BaseCenterApp::Disconnected()
{

}

void BaseCenterApp::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
