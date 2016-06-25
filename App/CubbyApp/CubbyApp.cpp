#include "CubbyApp.h"

InitSingleton(CubbyApp)
CubbyApp::CubbyApp() :
mNetLogic(NULL),
mGCSession(NULL)
{
}

CubbyApp::~CubbyApp()
{
	Clear();
}

bool CubbyApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}
	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "CubbyApp config error!";
		return false;
	}
	mNetLogic = new CubbyNetLogic;
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT))
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

bool CubbyApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void CubbyApp::Clear()
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

void CubbyApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}