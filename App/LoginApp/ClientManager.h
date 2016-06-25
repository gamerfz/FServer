#pragma once
#include <Singleton.h>
#include "Client.h"

#define theClientMgr ClientManager::GetInstance()
class ClientManager : public Singleton<ClientManager>, public PoolManager<std::string, Client>
{
public:
	ClientManager();
	~ClientManager();

	Client* GetClientByAccount(const std::string& account);
};