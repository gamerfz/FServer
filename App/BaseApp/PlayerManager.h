#pragma once
#include <Singleton.h>
#include "Player.h"

#define thePlayerMgr PlayerManager::GetInstance()
class PlayerManager : public Singleton<PlayerManager>, public PoolManager<int, Player>
{
public:
	PlayerManager();
	~PlayerManager();
};