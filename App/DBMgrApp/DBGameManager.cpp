#include "DBGameManager.h"
#include "ConfigManager.h"

InitSingleton(DBGameManager)
DBGameManager::DBGameManager()
{
}

DBGameManager::~DBGameManager()
{
}

bool DBGameManager::ConnectMysql()
{
	for (auto it : *theConfigMgr->GetDBCfgMap())
	{
		if (it.second.type == EDBT_Game)
		{
			auto dbGame = std::make_shared<DBGame>();
			dbGame->Init(it.second.name, it.second.user, it.second.password, it.second.host, it.second.port);
			if (!dbGame->Connect())
				return false;
			mmapDBGame.insert(std::make_pair(it.first, dbGame));
			dbGame->SetDBID(it.first);
		}
	}

	return true;
}

GP_PTR<DBGame> DBGameManager::GetDBGame(int id)
{
	auto it = mmapDBGame.find(id);
	if (it != mmapDBGame.end())
		return it->second;
	return NULL;
}

GP_PTR<DBGame> DBGameManager::GetDBGame(std::string& name)
{
	for (auto it : *theConfigMgr->GetDBCfgMap())
	{
		if (it.second.name == name)
			return GetDBGame(it.first);
	}
	return NULL;
}