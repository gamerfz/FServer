#pragma once
#include <Singleton.h>
#include "BCNetLogic.h"
#include "ConfigManager.h"
#include "DBSession.h"

#define theBaseCenterApp BaseCenterApp::GetInstance()
class BaseCenterApp : public Singleton<BaseCenterApp>
{
	BCNetLogic* mNetLogic;
	DBSession* mDBSession;
public:
	BaseCenterApp();
	~BaseCenterApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	BCNetLogic* GetNetLogic() const { return mNetLogic; }
};