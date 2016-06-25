#pragma once
#include <NetInterface.h>

class DBNetLogic : public NetInterface
{
public:
	DBNetLogic();
	~DBNetLogic();

	void OnMessage(const NetPacket& packet);

	void OnRegisterApp(const NetMessage* nmsg, int fd);
	void OnUnRegisterApp(const NetMessage* nmsg);
};