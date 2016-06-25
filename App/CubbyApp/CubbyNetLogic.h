#pragma once
#include <NetInterface.h>

class CubbyNetLogic : public NetInterface
{
public:
	CubbyNetLogic();
	~CubbyNetLogic();

	void OnMessage(const NetPacket& packet);
};