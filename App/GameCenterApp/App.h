#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "GameCenterApp.h"

class App : public AppSession
{
public:
	App();
	~App();

	bool SendToApp(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	void OnGameMsg(const NetMessage* nmsg, int msgType = 0);
	void OnCubbyMsg(const NetMessage* nmsg, int msgType = 0);
};
