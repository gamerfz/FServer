/***********************************************************************
*FileName	:  RedisConnect
*Author		:  fz
*Date		:  2016.2.25
*Description:  hiredis封装类(简单的实现了基础数据和hash操作)
************************************************************************/
#pragma once
#include <string>
#include <map>
#include <set>
#include "redis/deps/hiredis/hiredis.h"


class RedisConnect
{
	redisContext* mContext;
	redisReply* mReply;
	std::string mHost;
	int mPort;
	int mDBCnt;
	std::string mPassword;
public:
	RedisConnect();
	~RedisConnect();

	bool Init(const std::string& host, int port, const std::string& password = "");
	void Finis();

	//int GetKeyType(const char* key);
	bool ExistsKey(const char* key);
	bool DelKey(const char* key);
	bool SetInt(const char* key, const int& value);
	bool GetInt(const char* key, int& value);
	bool SetLong(const char* key, const long long& value);
	bool GetLong(const char* key, long long& value);
	bool SetStr(const char* key, const char* value);
	bool GetStr(const char* key, std::string& value);
	bool SetBin(const char* key, const char* value, int len);
	bool GetBin(const char* key, std::string &value);
	bool SetHset(const char* key, const char* field, const char* value);
	bool GetHset(const char* key, const char* field, std::string& value);
	bool SetHMset(const char* key, std::map<std::string, std::string> fieldValue);
	bool GetHMset(const char* key, const std::set<std::string>& fieldSet, std::map<std::string, std::string>& fieldValue);
	
	redisContext* GetContext() { return mContext; }
	redisReply* GetReply() { return mReply; }
};
