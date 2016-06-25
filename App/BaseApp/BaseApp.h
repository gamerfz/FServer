#pragma once
#include <Singleton.h>
#include "ConfigManager.h"
#include "BaseNetLogic.h"
#include "BCSession.h"
#include "DBSession.h"
#include "GameSession.h"

#define theBaseApp BaseApp::GetInstance()
class BaseApp : public Singleton<BaseApp>
{
	BaseNetLogic* mNetLogic;
	BCSession* mBCSession;
	DBSession* mDBSession;
	GameSession* mGameSession;
public:
	BaseApp();
	~BaseApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	BaseNetLogic* GetNetLogic() const { return mNetLogic; }
	BCSession* GetBCSession() const { return mBCSession; }
	DBSession* GetDBSession() const { return mDBSession; }
	GameSession* GetGameSession() const { return mGameSession; }
};