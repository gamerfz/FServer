#pragma once
#include <NetInterface.h>

class GCNetLogic : public NetInterface
{
public:
	GCNetLogic();
	~GCNetLogic();

	void OnMessage(const NetPacket& packet);

	void OnRegisterApp(const NetMessage* nmsg, int fd);
	void OnUnRegisterApp(const NetMessage* nmsg);
};