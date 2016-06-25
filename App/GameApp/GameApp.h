#pragma once
#include <Singleton.h>
#include "GameNetLogic.h"
#include "GCSession.h"
#include "ConfigManager.h"

#define theGameApp GameApp::GetInstance()
class GameApp : public Singleton<GameApp>
{
	GameNetLogic* mNetLogic;
	GCSession* mGCSession;
public:
	GameApp();
	~GameApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	GameNetLogic* GetNetLogic() const { return mNetLogic; }
	GCSession* GetGCSession() const { return mGCSession; }
};