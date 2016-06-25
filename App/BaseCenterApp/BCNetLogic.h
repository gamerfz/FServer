#pragma once
#include <NetInterface.h>

class BCNetLogic : public NetInterface
{
public:
	BCNetLogic();
	~BCNetLogic();

	void OnMessage(const NetPacket& packet);

	void OnRegisterApp(const NetMessage* nmsg, int fd);
	void OnUnRegisterApp(const NetMessage* nmsg);
};