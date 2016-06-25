#pragma once
#include <ServerSession.h>

class GCSession : public ServerSession
{
public:
	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	bool SendToGC(::google::protobuf::Message* pbMsg);
};