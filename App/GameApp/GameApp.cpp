#include "GameApp.h"

InitSingleton(GameApp)
GameApp::GameApp() :
mNetLogic(NULL),
mGCSession(NULL)
{
}

GameApp::~GameApp()
{
	Clear();
}

bool GameApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}
	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "GameApp config error!";
		return false;
	}
	/*每个gameapp只是监听了自己的baseapp,理论上只需要1条连接1个线程,预留少量多余连接*/
	mNetLogic = new GameNetLogic;
	if (!mNetLogic->Init(cfg->serverPort, 100, 1))
	{
		LOG(ERROR) << "NetLogic init failed!";
		return false;
	}

	auto gcCfg = theConfigMgr->GetServerCfg(ESAI_GameCenterApp);
	if (!gcCfg)
	{
		LOG(ERROR) << "GameCenterApp config error!";
		return false;
	}
	mGCSession = new GCSession;
	if (!mGCSession->Connect(mNetLogic, gcCfg->serverIP, gcCfg->serverPort, RECONNECT_MSEC))
	{
		LOG(ERROR) << "Connect GameCenterApp error!";
		return false;
	}
	return true;
}

bool GameApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void GameApp::Clear()
{
	if (mNetLogic)
	{
		delete mNetLogic;
		mNetLogic = NULL;
	}
	if (mGCSession)
	{
		delete mGCSession;
		mGCSession = NULL;
	}
}

void GameApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}