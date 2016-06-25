/***********************************************************************
*FileName	:  ServerSession
*Author		:  fz
*Date		:  2016.1.17
*Description:  服务端会话(当本地为Client主动请求连接时)
************************************************************************/
#pragma once
#include "BaseSession.h"
#include "TimerEvent.h"
#include "NetInterface.h"

enum ServerSessionStatus
{
	ESSS_Default = 0,
	ESSS_Connecting = 1,
	ESSS_Connected = 2,
	ESSS_Final = 3,
};

class ServerSession;
class ConnectEvent : public TimerEvent
{
	std::string mstrIP;
	int mPort;
	NetInterface* mNetInterface;
	ServerSession* mSession;
	ServerSessionStatus mSSStatus;
public:
	ConnectEvent(NetInterface* nif, ServerSession* session, const std::string& ip, int port, int msec);
	virtual~ConnectEvent();
	
	virtual void OnTimer();
	bool Reconnect();
	void Disconnect();
	ServerSessionStatus GetSStatus() { return mSSStatus; }
};

class ServerSession : public BaseSession
{
	ConnectEvent* mConnectEvent;
	bool mRepeated;
public:
	ServerSession();
	virtual~ServerSession();

	virtual void Disconnected()
	{
		if (mConnectEvent && mRepeated)
			mConnectEvent->Reconnect();
	}
	virtual void Clear() {}
	ServerSessionStatus GetSStatus() { return mConnectEvent->GetSStatus(); }
	bool Connect(NetInterface* nif, const std::string& ip, int port, int msec, bool repeated = true);
};
