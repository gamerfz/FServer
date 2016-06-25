#pragma once
#include <Singleton.h>
#include "App.h"

#define theAppMgr AppManager::GetInstance()
class AppManager : public Singleton<AppManager>, public PoolManager<APP_ID, App>
{
public:
	AppManager();
	~AppManager();
};