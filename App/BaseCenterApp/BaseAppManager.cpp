#include "BaseAppManager.h"

InitSingleton(BaseAppManager)
BaseAppManager::BaseAppManager()
{
	
}

BaseAppManager::~BaseAppManager()
{
}

GP_PTR<BaseApp> BaseAppManager::DispatchBaseApp()
{
// 	int appid = 0;
// 	int min = 0;
	for (auto it : mmapBaseApp)
	{
		return it.second;
	}

	return NULL;
}