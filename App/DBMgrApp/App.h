#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "DBMgrApp.h"

class App : public AppSession
{
public:
	App();
	~App();

	bool SendToApp(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	void OnBCMsg(const NetMessage* nmsg, int msgType = 0);
	void OnBaseMsg(const NetMessage* nmsg, int msgType = 0);
	void OnLoginMsg(const NetMessage* nmsg, int msgType = 0);
};
