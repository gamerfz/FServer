#include "LoginApp.h"
#include "ConfigManager.h"

InitSingleton(LoginApp)
LoginApp::LoginApp() :
mNetLogic(NULL),
mBCSession(NULL),
mLoginLevel(ACCOUNT_LEVEL_DEFAULT)
{
}

LoginApp::~LoginApp()
{
	Clear();
}

bool LoginApp::Init()
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

	mNetLogic = new LoginNetLogic;
	/*由于直接和登陆挂钩，为防止大量频繁或无效登陆,可以尽量多开几个IO线程应对，一般单个LoginApp已经足够，如有需求可以修改为多个LoginApp，相应也要调整Client的登录策略*/
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT, 8))
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
		return false;
	/*设置当前可以登录的帐号等级 暂时不做限制开放所有等级*/
	SetLoginLevel(ACCOUNT_LEVEL_ALL /*ACCOUNT_LEVEL_ADMINISTRATOR | ACCOUNT_LEVEL_GAMEMASTER*/);
	return true;
}

void LoginApp::Clear()
{
	mLoginLevel = ACCOUNT_LEVEL_DEFAULT;
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
}

bool LoginApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void LoginApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}

bool LoginApp::CheckLoginLevel(short lvl)
{
	return mLoginLevel & lvl;
}