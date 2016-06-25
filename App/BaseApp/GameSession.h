/*当前框架设定每个baseapp只有一个对应的gameapp*/
#pragma once
#include <ServerSession.h>
#include "ServerMsg.pb.h"

class GameSession : public ServerSession
{
public:
	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	bool SendToGame(::google::protobuf::Message* pbMsg);
};
