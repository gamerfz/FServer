#pragma once
#include <unordered_map>
#include <Singleton.h>
#include <GPDef.h>
#include <PoolManager.h>
#include "BCPlayer.h"

#define theBCPlayerMgr BCPlayerManager::GetInstance()
class BCPlayerManager : public Singleton<BCPlayerManager>, public PoolManager<int, BCPlayer>
{
public:
	BCPlayerManager();
	~BCPlayerManager();
};
