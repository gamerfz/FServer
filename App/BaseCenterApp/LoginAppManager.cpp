#include "LoginAppManager.h"

InitSingleton(LoginAppManager)
LoginAppManager::LoginAppManager()
{

}

LoginAppManager::~LoginAppManager()
{
}

GP_PTR<LoginApp> LoginAppManager::GetLoginApp(APP_ID id)
{
	auto it = mmapLoginApp.find(id);
	if (it != mmapLoginApp.end())
		return it->second;
	return NULL;
}