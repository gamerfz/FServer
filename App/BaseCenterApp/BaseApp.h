#pragma once
#include <PoolManager.h>
#include <GPDef.h>

class BaseApp
{
	APP_ID mAppID;
public:
	BaseApp();
	~BaseApp();

	void SetAppID(APP_ID appid) { mAppID = appid; }
	APP_ID GetAppID() const { return mAppID; }
};