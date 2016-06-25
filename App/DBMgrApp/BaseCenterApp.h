#pragma once
#include <AppSession.h>
#include "DBMgrApp.h"

class BaseCenterApp : public AppSession
{
public:
	BaseCenterApp();
	~BaseCenterApp();

	bool SentToBC(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};