#pragma once
#include <vector>
#include <Singleton.h>
#include <GPDef.h>
#include "DBGlobal.h"

#define theDBGlobalMgr DBGlobalManager::GetInstance()
class DBGlobalManager : public Singleton<DBGlobalManager>
{
	GP_PTR<DBGlobal> mDBGlobal;
	int mDBID;
public:
	DBGlobalManager();
	~DBGlobalManager();

	bool ConnectMysql();

	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlResult& sqlResult);//SELECT
	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlExcuteResult& sqlResult);//INSERT UPDATE DELETE

	void SetDBID(int id) { mDBID = id; }
};