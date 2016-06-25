#pragma once
#include <NetInterface.h>

class BaseNetLogic : public NetInterface
{
public:
	BaseNetLogic();
	~BaseNetLogic();

	void OnMessage(const NetPacket& packet);
};