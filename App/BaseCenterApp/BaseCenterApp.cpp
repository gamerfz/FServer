#include "BaseCenterApp.h"
#include "ConfigManager.h"

InitSingleton(BaseCenterApp)
BaseCenterApp::BaseCenterApp() :
mNetLogic(NULL)
{
}

BaseCenterApp::~BaseCenterApp()
{
	Clear();
}

bool BaseCenterApp::Init()
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

	mNetLogic = new BCNetLogic;
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT))
	{
		LOG(ERROR) << "NetLogic init failed!";
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

	return true;
}

bool BaseCenterApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void BaseCenterApp::Clear()
{
	if (mNetLogic)
	{
		delete mNetLogic;
		mNetLogic = NULL;
	}
}

void BaseCenterApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}