#pragma once
#include <ServerSession.h>
#include "ServerMsg.pb.h"

class DBSession : public ServerSession
{
public:
	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	bool SendToDB(::google::protobuf::Message* pbMsg);
};
