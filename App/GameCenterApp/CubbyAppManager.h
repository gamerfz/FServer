#pragma once
#include <Singleton.h>
#include "CubbyApp.h"

#define theCubbyAppMgr CubbyAppManager::GetInstance()
class CubbyAppManager : public Singleton<CubbyAppManager>, public PoolManager<CubbyApp>
{
public:
	CubbyAppManager();
	~CubbyAppManager();
};