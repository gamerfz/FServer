#pragma once
#include <GPDef.h>
#include <PoolManager.h>

class BCPlayer : public PoolObject
{
	/*ËùÔÚbaseµÄAppID*/
	APP_ID mAppID;
	/*guid*/
	unsigned long long mGuid;
public:
	BCPlayer();
	~BCPlayer();

	virtual void OnReset();
};
