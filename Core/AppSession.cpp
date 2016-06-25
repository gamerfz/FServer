#include "AppSession.h"

AppSession::AppSession()
{
}

AppSession::~AppSession()
{
}

void AppSession::OnReset()
{
	SetFD(-1);
	SetIndex(-1);
	mAppID = 0;
	mAppType = 0;
}

void AppSession::Connected()
{

}

void AppSession::Disconnected()
{

}

void AppSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
