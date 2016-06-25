#pragma once
#include <Singleton.h>
#include "GameApp.h"

#define theGameAppMgr GameAppManager::GetInstance()
class GameAppManager : public Singleton<GameAppManager>, public PoolManager<GameApp>
{
public:
	GameAppManager();
	~GameAppManager();
};