#include "GameCenterApp.h"
#include "ConfigManager.h"

InitSingleton(GameCenterApp)
GameCenterApp::GameCenterApp() :
mNetLogic(NULL),
mBCSession(NULL),
mDBSession(NULL)
{
}

GameCenterApp::~GameCenterApp()
{
	Clear();
}

bool GameCenterApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}

	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "Server config error!";
		return false;
	}

	mNetLogic = new GCNetLogic;
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT))
	{
		LOG(ERROR) << "NetLogic init failed!";
		return false;
	}

	auto bcCfg = theConfigMgr->GetServerCfg(ESAI_BaseCenterApp);
	if (!bcCfg)
	{
		LOG(ERROR) << "BaseCenterApp config error!";
		return false;
	}
	mBCSession = new BCSession;
	if (!mBCSession->Connect(mNetLogic, bcCfg->serverIP, bcCfg->serverPort, RECONNECT_MSEC))
	{
		LOG(ERROR) << "Connect BaseCenterApp error!";
		return false;
	}

	auto dbCfg = theConfigMgr->GetServerCfg(ESAI_DBMgrApp);
	if (!dbCfg)
	{
		LOG(ERROR) << "DBMgrApp config error!";
		return false;
	}

	mDBSession = new DBSession;/*暂时不用连接DB*/
// 	if (!mDBSession->Connect(mNetLogic, dbCfg->serverIP, dbCfg->serverPort, RECONNECT_MSEC))
// 	{
// 		LOG(ERROR) << "Connect DBMgrApp error!";
// 		return false;
// 	}

	return true;
}

bool GameCenterApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void GameCenterApp::Clear()
{
	if (mNetLogic)
	{
		delete mNetLogic;
		mNetLogic = NULL;
	}
	if (mBCSession)
	{
		delete mBCSession;
		mBCSession = NULL;
	}
	if (mDBSession)
	{
		delete mDBSession;
		mDBSession = NULL;
	}
}

void GameCenterApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}