/*服务端数据枚举等定义*/
#pragma once
#include <GPDef.h>

#define MAX_PLAYER_COUNT 5000
#define MAX_CONNECT_COUNT 10000
#define RECONNECT_MSEC 1000 //毫秒


/*服务器App类型定义*/
enum ServerAppType
{
	ESAT_Unknown = 0,
	ESAT_DBMgr,
	ESAT_Base,
	ESAT_BaseCenter,
	ESAT_Game,
	ESAT_GameCenter,
	ESAT_Cubby,
	ESAT_Login,
	ESAT_Payment,
	ESAT_Interface,
};

/*服务器AppID定义*/
enum ServerAppID
{
	ESAI_Unknown = 0,
	ESAI_DBMgrApp,
	ESAI_BaseCenterApp,
	ESAI_GameCenterApp,
	ESAI_LoginApp,
	ESAI_PaymentApp,
	ESAI_InterfaceApp,

	/*baseapp为100起的偶数,+1即为对应的gameapp*/
	ESAI_MinBaseApp = 100,
	ESAI_MinGameApp = 101,

	ESAI_MaxBaseApp = 998,
	ESAI_MaxGameApp = 999
};

/*数据库类型*/
enum DBType
{
	EDBT_Unknown = 0,
	EDBT_Global,
	EDBT_Game,
	EDBT_Log,
};

/*帐号权限 LoginApp根据此权限管理登录*/
#define ACCOUNT_LEVEL_DEFAULT			0x00	//默认无任何权限
#define ACCOUNT_LEVEL_ADMINISTRATOR		0x01	//管理员
#define ACCOUNT_LEVEL_GAMEMASTER		0x02	//GM
#define ACCOUNT_LEVEL_ALPHA				0x04	//a测帐号
#define ACCOUNT_LEVEL_BETA				0x08	//b测帐号
#define ACCOUNT_LEVEL_GAMER				0x10	//正式帐号
#define ACCOUNT_LEVEL_FREE				0x20	//
#define ACCOUNT_LEVEL_UNDER_AGE			0x40	//未成年
#define ACCOUNT_LEVEL_128				0x80	//
#define ACCOUNT_LEVEL_ALL				0xff	//All


/*安全的释放一个指针内存*/
#define SAFE_DELETE(i) if (i){ delete i; i = NULL;}
/*安全的释放一个指针数组内存*/
#define SAFE_DELETE_ARRAY(i) if (i){ delete[] i; i = NULL;}
