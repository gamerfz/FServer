#include "AppManager.h"

InitSingleton(AppManager)
AppManager::AppManager()
{
	InitPool();
}

AppManager::~AppManager()
{
}