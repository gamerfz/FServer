#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "GameCenterApp.h"

class CubbyApp : public AppSession
{
public:
	CubbyApp();
	~CubbyApp();

	bool SentToCubby(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};