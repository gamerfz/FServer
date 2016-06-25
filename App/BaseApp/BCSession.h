#pragma once
#include <ServerSession.h>
#include "ServerMsg.pb.h"

class BCSession : public ServerSession
{
public:
	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	bool SendToBC(::google::protobuf::Message* pbMsg);


	void OnMsgRespondApp(MsgRespondApp* msg);

};
