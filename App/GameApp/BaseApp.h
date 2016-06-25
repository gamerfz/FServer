#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "GameApp.h"

class BaseApp : public AppSession
{
public:
	BaseApp();
	~BaseApp();

	bool SendToApp(::google::protobuf::Message* pbMsg);//不用SendToBase命名,统一将监听端App发送的其他App的消息接口命名为SendToApp

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);
};