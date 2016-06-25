#pragma once
#include <map>
#include <Singleton.h>
#include <GPDef.h>
#include "DBGame.h"

#define theDBGameMgr DBGameManager::GetInstance()
class DBGameManager : public Singleton<DBGameManager>
{
	std::map<int, GP_PTR<DBGame>> mmapDBGame;
public:
	DBGameManager();
	~DBGameManager();

	bool ConnectMysql();
	//æ°¡ø”√ID
	GP_PTR<DBGame> GetDBGame(int id);
	GP_PTR<DBGame> GetDBGame(std::string& name);
};
