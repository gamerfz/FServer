#pragma once
#include <vector>
#include <map>
#include <string>
#include "ServerDefine.h"

/*xml文件目录*/
#define SERVERCONFIG_DIR "./Resource/Config/ServerConfig.xml"	//服务器app配置
#define ROBOTCONFIG_DIR "./Resource/Config/RobotConfig.xml"	//机器人app配置
#define GAMECONFIG_DIR "./Resource/Config/GameConfig.xml" //游戏配置
#define DBCONFIG_DIR "./Resource/Config/DBConfig.xml" //数据库连接配置

struct ServerCfg
{
	int appID;//服务端之间AppID
	std::string serverIP;
	int serverPort;
	ServerCfg(){ Clear(); }
	void Clear()
	{
		appID = ESAI_Unknown;
		serverIP = "";
		serverPort = 0;
	}
};

struct RobotCfg
{
	int appID;//1本地配置, 2目标服务器配置
	std::string serverIP;
	int serverPort;
	int count;
	RobotCfg(){ Clear(); }
	void Clear()
	{
		appID = 0;
		serverIP = "";
		serverPort = 0;
		count = 0;
	}
};

struct DBCfg
{
	DBType		type;					//数据库类型
	std::string name;					//数据库名
	std::string user;					//登录的用户名
	std::string password;				//登录的密码
	std::string host;					//数据库地址
	int port;							//数据库端口
	DBCfg(){ Clear(); }
	void Clear()
	{
		type = EDBT_Unknown;
		name = "";
		user = "";
		password = "";
		host = "";
		port = 0;
	}
};