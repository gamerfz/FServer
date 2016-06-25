#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "GameCenterApp.h"

class GameApp : public AppSession
{
public:
	GameApp();
	~GameApp();

	bool SentToGame(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};