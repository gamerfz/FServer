#pragma once
#include <NetInterface.h>

class LoginNetLogic : public NetInterface
{
public:
	LoginNetLogic();
	~LoginNetLogic();

	void OnMessage(const NetPacket& packet);

	void OnRegisterClient(const NetMessage* nmsg, int fd);
	void OnUnRegisterClient(const NetMessage* nmsg);
};