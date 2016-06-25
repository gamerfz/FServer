#pragma once
#include <BaseSession.h>
#include <PoolManager.h>
#include "LoginApp.h"

class Client : public BaseSession, public PoolObject
{
	int mClientID;
	std::string mAccount;
public:
	Client();
	~Client();

	virtual void OnReset();
	bool SendToClient(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	void SetClientID(int clientid) { mClientID = clientid; }
	int GetClientID() const { return mClientID; }
	void SetAccount(std::string account) { mAccount = account; }
	std::string GetAccount() const { return mAccount; }
};