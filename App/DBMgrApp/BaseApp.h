#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "DBMgrApp.h"

class BaseApp : public AppSession
{
public:
	BaseApp();
	~BaseApp();

	bool SentToBase(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};