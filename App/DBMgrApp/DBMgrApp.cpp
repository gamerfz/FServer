#include "DBMgrApp.h"
#include "DBGameManager.h"
#include "DBGlobalManager.h"

InitSingleton(DBMgrApp)
DBMgrApp::DBMgrApp() :
mNetLogic(NULL)
{
}

DBMgrApp::~DBMgrApp()
{
	Clear();
}

bool DBMgrApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}
	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "DBMgrApp config error!";
		return false;
	}

	if (!theDBGlobalMgr->ConnectMysql() || !theDBGameMgr->ConnectMysql())
	{
		LOG(ERROR) << "Connect mysql failed!";
		return false;
	}


	mNetLogic = new DBNetLogic;
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT))
	{
		LOG(ERROR) << "NetLogic init failed!";
		return false;
	}

/*
	SqlExcuteResult eRes;
	SqlParams params;
	SqlResult res;
	params.push_back("95431");
	theDBGame->SqlExcute("INSERT INTO game (password) VALUES (%0q);", params, eRes);
	theDBGame->SqlExcute("SELECT * FROM game WHERE id = %0;", params, res);*/

	return true;
}

bool DBMgrApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void DBMgrApp::Clear()
{
	if (mNetLogic)
	{
		delete mNetLogic;
		mNetLogic = NULL;
	}
}

void DBMgrApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}