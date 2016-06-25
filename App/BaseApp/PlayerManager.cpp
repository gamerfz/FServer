#include "PlayerManager.h"

InitSingleton(PlayerManager)
PlayerManager::PlayerManager()
{
	InitPool();
}

PlayerManager::~PlayerManager()
{
}