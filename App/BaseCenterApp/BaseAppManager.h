#pragma once
#include <map>
#include <Singleton.h>
#include <GPDef.h>
#include "BaseApp.h"

#define theBaseAppMgr BaseAppManager::GetInstance()
class BaseAppManager : public Singleton<BaseAppManager>
{
	std::map<APP_ID, GP_PTR<BaseApp>> mmapBaseApp;
	int mCurIndex;
public:
	BaseAppManager();
	~BaseAppManager();

	GP_PTR<BaseApp> DispatchBaseApp();
};