#include "BaseAppManager.h"

InitSingleton(BaseAppManager)
BaseAppManager::BaseAppManager()
{
	InitPool(1);
}

BaseAppManager::~BaseAppManager()
{
}