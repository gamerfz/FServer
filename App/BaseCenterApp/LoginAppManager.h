#pragma once
#include <map>
#include <Singleton.h>
#include <GPDef.h>
#include "LoginApp.h"

#define theLoginAppMgr LoginAppManager::GetInstance()
class LoginAppManager : public Singleton<LoginAppManager>
{
	std::map<APP_ID, GP_PTR<LoginApp>> mmapLoginApp;
public:
	LoginAppManager();
	~LoginAppManager();

	GP_PTR<LoginApp> GetLoginApp(APP_ID id);
};