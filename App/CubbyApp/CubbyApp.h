#pragma once
#include <Singleton.h>
#include "CubbyNetLogic.h"
#include "GCSession.h"
#include "ConfigManager.h"

#define theCubbyApp CubbyApp::GetInstance()
class CubbyApp : public Singleton<CubbyApp>
{
	CubbyNetLogic* mNetLogic;
	GCSession* mGCSession;
public:
	CubbyApp();
	~CubbyApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	CubbyNetLogic* GetNetLogic() const { return mNetLogic; }
	GCSession* GetGCSession() const { return mGCSession; }
};