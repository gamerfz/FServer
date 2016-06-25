#pragma once
#include <Singleton.h>
#include "BaseApp.h"

#define theBaseAppMgr BaseAppManager::GetInstance()
class BaseAppManager : public Singleton<BaseAppManager>, public PoolManager<BaseApp>
{
public:
	BaseAppManager();
	~BaseAppManager();
};