#pragma once
#include <unordered_map>
#include <GPDef.h>

class LoginApp
{
	APP_ID mAppID;
	std::unordered_map<int, int> mumapPendingLogin;
public:
	LoginApp();
	~LoginApp();

	void SetAppID(APP_ID appid) { mAppID = appid; }
	APP_ID GetAppID() const { return mAppID; }

};