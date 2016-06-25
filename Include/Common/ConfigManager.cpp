#include "ConfigManager.h"
#include <Xml.h>
#include <glog/glog.h>

InitSingleton(ConfigManager)

ConfigManager::ConfigManager() :
mAppID(ESAI_Unknown)
{
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::ParseCommond(int argc, char* argv[])
{
	if (argc < 2)//0进程路径名字 1appid
		return false;
	std::string cmd = argv[1];
	std::string findcmd = "--appid=";
	std::string::size_type fi = cmd.find(findcmd);
	if (fi == std::string::npos)
		return false;
	cmd.erase(fi, findcmd.size());
	if (!cmd.size())
		return false;

	mAppID = atoi(cmd.c_str());
	return mAppID != ESAI_Unknown;
}

bool ConfigManager::LoadingConfig()
{
	switch (mAppID)
	{
	case ESAI_Unknown:
		return false;
	case ESAI_DBMgrApp:
		return LoadSeverConfig() && LoadGameConfig() && LoadDBConfig();
	case ESAI_LoginApp:
		return LoadSeverConfig() && LoadGameConfig();
	default:
		break;
	}
	return LoadingAll();
}

bool ConfigManager::LoadingAll()
{
	return
		LoadSeverConfig() && LoadGameConfig();
}

bool ConfigManager::LoadSeverConfig()
{
	XmlDocument xml;
	xml.LoadFile(SERVERCONFIG_DIR);

	auto root = xml.FirstChildElement();
	if (!root)
		return false;
	
	ServerCfg acfg;
	auto it = root->GetNode();
	while (it)
	{
		if (!it->Attribute("AppID") || !it->Attribute("IP") || !it->Attribute("Port"))
			return false;
		acfg.Clear();
		acfg.appID = atoi(it->Attribute("AppID"));
		acfg.serverIP = it->Attribute("IP");
		acfg.serverPort = atoi(it->Attribute("Port"));
		mmapServerCfg.insert(std::make_pair(acfg.appID, acfg));
		it = it->NextSibling();
	}
	LOG(INFO) << "Server config ok";
	return true;

	/*
	auto dbMgrEmt = root->GetNode("DBMgr");
	if (dbMgrEmt)
	{
	if (!dbMgrEmt->Attribute("Aid") || !dbMgrEmt->Attribute("IP") || !dbMgrEmt->Attribute("Port"))
	return false;
	acfg.Clear();
	acfg.aid = atoi(dbMgrEmt->Attribute("Aid"));
	acfg.serverIP = dbMgrEmt->Attribute("IP");
	acfg.serverPort = atoi(dbMgrEmt->Attribute("Port"));
	mmapServer.insert(std::make_pair(acfg.aid, acfg));
	// 		if (!dbMgrEmt->GetNode("IP") || !dbMgrEmt->GetNode("Port"))
	// 			return false;
	// 		if (dbMgrEmt->GetNode("IP")->Attribute("id"))
	// 			acfg.type = atoi(dbMgrEmt->GetNode("IP")->Attribute("id"));
	// 		acfg.Clear();
	// 		acfg.serverIP = dbMgrEmt->GetNode("IP")->value();
	// 		acfg.serverPort = atoi(dbMgrEmt->GetNode("Port")->value());
	// 		acfg.type = 0;// ESAT_DBMgr;
	// 		mmapServer.insert(std::make_pair(acfg.type, acfg));
	}*/
}

bool ConfigManager::LoadRobotConfig()
{
	XmlDocument xml;
	xml.LoadFile(ROBOTCONFIG_DIR);

	auto root = xml.FirstChildElement();
	if (!root)
		return false;

	RobotCfg acfg;
	auto it = root->GetNode();
	while (it)
	{
		if (!it->Attribute("AppID") || !it->Attribute("IP") || !it->Attribute("Port"))
			return false;
		acfg.Clear();
		acfg.appID = atoi(it->Attribute("AppID"));
		acfg.serverIP = it->Attribute("IP");
		acfg.serverPort = atoi(it->Attribute("Port"));
		if (it->Attribute("Count"))
			acfg.count = atoi(it->Attribute("Count"));
		mmapRobotCfg.insert(std::make_pair(acfg.appID, acfg));
		it = it->NextSibling();
	}
	LOG(INFO) << "Robot config ok";
	return true;
}

bool ConfigManager::LoadGameConfig()
{
	XmlDocument xml;
	xml.LoadFile(GAMECONFIG_DIR);

	auto root = xml.FirstChildElement();
	if (!root)
		return false;

	auto it = root->GetNode();
	while (it)
	{
		mmapGameCfg.insert(std::make_pair(it->name(), it->value()));
		it = it->NextSibling();
	}
	LOG(INFO) << "Game config ok";
	return true;
}

bool ConfigManager::LoadDBConfig()
{
	XmlDocument xml;
	xml.LoadFile(DBCONFIG_DIR);

	auto root = xml.FirstChildElement();
	if (!root)
		return false;

	DBCfg acfg;
	std::string nodeName;
	int idx = 0;
	auto it = root->GetNode();
	while (it)
	{
		acfg.Clear();
		nodeName = it->name();
		if (nodeName == "Global")
			acfg.type = EDBT_Global;
		else if (nodeName == "Game")
			acfg.type = EDBT_Game;
		else if (nodeName == "Log")
			acfg.type = EDBT_Log;
		else
		{
			LOG(ERROR) << "Unknown DB!" << LogValue("name", it->name());
			continue;
		}
		if (!it->Attribute("Name") || !it->Attribute("User") || !it->Attribute("Password") ||
			!it->Attribute("Host") || !it->Attribute("Port"))
			return false;
		acfg.name = it->Attribute("Name");
		acfg.user = it->Attribute("User");
		acfg.password = it->Attribute("Password");
		acfg.host = it->Attribute("Host");
		acfg.port = atoi(it->Attribute("Port"));
		mmapDBCfg.insert(std::make_pair(idx, acfg));
		idx++;
		it = it->NextSibling();
	}
	LOG(INFO) << "DB config ok";
	return true;
}


ServerCfg* ConfigManager::GetServerCfg(int appid)
{
	auto it = mmapServerCfg.find(appid);
	if (it != mmapServerCfg.end())
		return &it->second;
	return NULL;
}

RobotCfg* ConfigManager::GetRobotCfg(int appid)
{
	auto it = mmapRobotCfg.find(appid);
	if (it != mmapRobotCfg.end())
		return &it->second;
	return NULL;
}

int ConfigManager::GetConfigVal(std::string s)
{
	auto it = mmapGameCfg.find(s);
	if (it != mmapGameCfg.end())
		return atoi(it->second.c_str());
	return 0;
}

std::string ConfigManager::GetConfigStr(std::string s)
{
	auto it = mmapGameCfg.find(s);
	if (it != mmapGameCfg.end())
		return it->second.c_str();
	return "";
}

void ConfigManager::GetConfigArray(std::string s, std::string sign, std::vector<int>* vec)
{
	int begin = 0, end = 0;
	std::string str = GetConfigStr(s);
	do
	{
		end = str.find_first_of(sign);
		if (begin < str.size())
			vec->push_back(atoi(str.substr(begin, end - begin).data()));
		begin = end + 1;
	} while (end != std::string::npos);
}

DBCfg* ConfigManager::GetDBCfg(int id)
{
	auto it = mmapDBCfg.find(id);
	if (it != mmapDBCfg.end())
		return &it->second;
	return NULL;
}