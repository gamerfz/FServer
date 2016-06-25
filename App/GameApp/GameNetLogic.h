#pragma once
#include <NetInterface.h>

class GameNetLogic : public NetInterface
{
public:
	GameNetLogic();
	~GameNetLogic();

	void OnMessage(const NetPacket& packet);
};