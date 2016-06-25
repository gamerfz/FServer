#pragma once
#include <Singleton.h>
#include "GCNetLogic.h"
#include "ConfigManager.h"
#include "BCSession.h"
#include "DBSession.h"

#define theGameCenterApp GameCenterApp::GetInstance()
class GameCenterApp : public Singleton<GameCenterApp>
{
	GCNetLogic* mNetLogic;
	BCSession* mBCSession;
	DBSession* mDBSession;
public:
	GameCenterApp();
	~GameCenterApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	GCNetLogic* GetNetLogic() const { return mNetLogic; }
	BCSession* GetBCSession() const { return mBCSession; }
	DBSession* GetDBSession() const { return mDBSession; }
};