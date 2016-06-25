/***********************************************************************
*FileName	:  NetListener
*Author		:  fz
*Date		:  2016.1.17
*Description:  ÍøÂç¼àÌıÏß³Ì
************************************************************************/
#pragma once
#include <event.h>
#include <event2/listener.h>

class NetWork;

class NetListener
{
	event_base*	mEvBase;
	evconnlistener* mListener;
public:
	NetListener();
	~NetListener();

	bool StartListen(NetWork* net);
	bool StopListen();

private:
	static void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* saddr, int socklen, void* uData);
};