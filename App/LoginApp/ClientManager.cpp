#include "ClientManager.h"

InitSingleton(ClientManager)
ClientManager::ClientManager()
{
	InitPool(MAX_CONNECT_COUNT);
}

ClientManager::~ClientManager()
{
}

Client* ClientManager::GetClientByAccount(const std::string& account)
{
	for (auto it : GetObjectMap())
	{
		if (it.second->GetAccount() == account)
			return it.second;
	}
	return NULL;
}