#pragma once
#include <Singleton.h>
#include "BCSession.h"
#include "ConfigManager.h"
#include "LoginNetLogic.h"

#define theLoginApp LoginApp::GetInstance()
class LoginApp : public Singleton<LoginApp>
{
	LoginNetLogic* mNetLogic;
	BCSession* mBCSession;
	short mLoginLevel;//当前可登录的级别,掩码形式
public:
	LoginApp();
	~LoginApp();

	bool Init();
	void Clear();
	bool StartUp();
	void ShutDown();

	LoginNetLogic* GetNetLogic() const { return mNetLogic; }
	BCSession* GetBCSession() const { return mBCSession; }

	void SetLoginLevel(short lvl) { mLoginLevel = lvl; }
	bool CheckLoginLevel(short lvl);
};

