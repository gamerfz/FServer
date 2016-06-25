#pragma once
#include <Singleton.h>
#include "ConfigManager.h"
#include "DBNetLogic.h"

#define theDBMgrApp DBMgrApp::GetInstance()
class DBMgrApp : public Singleton<DBMgrApp>
{
	DBNetLogic* mNetLogic;
public:
	DBMgrApp();
	~DBMgrApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	DBNetLogic* GetNetLogic() const { return mNetLogic; }
	//BCSession* GetBCSession() const { return mBCSession; }
};