#pragma once
#include <string>
#include "Session.h"
#include "TimerEvent.h"
#include <event2/event.h>

class ClientSession : public BaseSession
{
	std::string mstrIP;
	int mPort;
	bool mConnected;
	TimerEvent* mTimer;
public:
	ClientSession(event_base* evBase, const std::string& ip, int port, int secs);
	virtual~ClientSession();

	virtual void OnTimer();
};


class ReconnectEvent : public TimerEvent
{
	std::string mstrIP;
	int mPort;
	bool mConnected;
public:
	ReconnectEvent(event_base* evBase, const std::string& ip, int port, int secs);
	virtual~ReconnectEvent();

	virtual void OnTimer();

	std::string GetIP() const { return mstrIP; }
	int GetPort() const { return mPort; }
	bool IsConnected() const { return mConnected; }
};
