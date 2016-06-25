#include "BaseApp.h"

InitSingleton(BaseApp)
BaseApp::BaseApp():
mNetLogic(NULL),
mBCSession(NULL),
mDBSession(NULL),
mGameSession(NULL)
{
}

BaseApp::~BaseApp()
{
	Clear();
}

bool BaseApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}
	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "BaseApp config error!";
		return false;
	}
	mNetLogic = new BaseNetLogic;
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
	mDBSession = new DBSession;
	if (!mDBSession->Connect(mNetLogic, dbCfg->serverIP, dbCfg->serverPort, RECONNECT_MSEC))
	{
		LOG(ERROR) << "Connect DBMgrApp error!";
		return false;
	}
	auto gCfg = theConfigMgr->GetServerCfg(theConfigMgr->GetGameAppID());
	if (!gCfg)
	{
		LOG(ERROR) << "GameApp config error!" << LogValue("appid", theConfigMgr->GetAppID());
		return false;
	}
	mGameSession = new GameSession;
	if (!mGameSession->Connect(mNetLogic, gCfg->serverIP, gCfg->serverPort, RECONNECT_MSEC))
	{
		LOG(ERROR) << "Connect GameApp error!";
		return false;
	}
	return true;
}

bool BaseApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void BaseApp::Clear()
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
	if (mGameSession)
	{
		delete mGameSession;
		mGameSession = NULL;
	}
}

void BaseApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}