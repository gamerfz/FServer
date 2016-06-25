#include "DBGlobalManager.h"
#include "ConfigManager.h"

InitSingleton(DBGlobalManager)
DBGlobalManager::DBGlobalManager()
{
}

DBGlobalManager::~DBGlobalManager()
{
}

bool DBGlobalManager::ConnectMysql()
{
	if (mDBGlobal)
		return false;
	for (auto it : *theConfigMgr->GetDBCfgMap())
	{
		if (it.second.type == EDBT_Global)
		{
			mDBGlobal = std::make_shared<DBGlobal>();
			mDBGlobal->Init(it.second.name, it.second.user, it.second.password, it.second.host, it.second.port);
			return mDBGlobal->Connect();
		}
	}

	return false;
}

bool DBGlobalManager::SqlExcute(const char* sql, SqlParams& sqlParams, SqlResult& sqlResult)
{
	if (!mDBGlobal)
		return false;
	return mDBGlobal->SqlExcute(sql, sqlParams, sqlResult);
}

bool DBGlobalManager::SqlExcute(const char* sql, SqlParams& sqlParams, SqlExcuteResult& sqlResult)
{
	if (!mDBGlobal)
		return false;
	return mDBGlobal->SqlExcute(sql, sqlParams, sqlResult);
}