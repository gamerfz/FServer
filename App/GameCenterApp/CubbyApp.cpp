#include "CubbyApp.h"

CubbyApp::CubbyApp()
{
}

CubbyApp::~CubbyApp()
{
}

bool CubbyApp::SentToCubby(::google::protobuf::Message* pbMsg)
{
	return theGameCenterApp->GetNetLogic()->OnSend(this, pbMsg);
}

void CubbyApp::Connected()
{

}

void CubbyApp::Disconnected()
{

}

void CubbyApp::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
