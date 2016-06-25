#include "RedisConnect.h"
#include <sstream>
#ifndef WIN32
#include <sys/time.h> /* for struct timeval */
#else
#include <event.h>/*偷个懒,直接用libevent获取timeval*/
#endif

RedisConnect::RedisConnect():
mContext(NULL),
mReply(NULL),
mHost(""),
mPort(0),
mPassword("")
{
}

RedisConnect::~RedisConnect()
{
	Finis();
}

bool RedisConnect::Init(const std::string& host, int port, const std::string& password /* = "" */)
{
	mHost = host;
	mPort = port;
	mPassword = password;

	Finis();
	timeval timeOut = { 1, 0 };//1秒超时
	mContext = redisConnectWithTimeout(mHost.c_str(), mPort, timeOut);
	if (!mContext)
	{
		return false;
	}
	else if (mContext->err)
	{
		redisFree(mContext);
		mContext = NULL;
		return false;
	}

	return true;
}

void RedisConnect::Finis()
{
	if (mReply)
	{
		freeReplyObject(mReply);
		mReply = NULL;
	}
	if (mContext)
	{
		redisFree(mContext);
		mContext = NULL;
	}
}

bool RedisConnect::ExistsKey(const char *key)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "EXISTS %s", key);
	if (!mReply)
		return false;
	else if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::DelKey(const char* key)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "DEL %s", key);
	if (!mReply)
		return false;
	else if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::SetInt(const char* key, const int& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "SET %s %lld", key, value);
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetInt(const char* key, int& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "GET %s", key);
	if (!mReply)
		return false;
	else
	{
		switch (mReply->type)
		{
		case REDIS_REPLY_INTEGER:
			{
				value = mReply->integer;
			}
			break;
		case REDIS_REPLY_STRING:
			{
				value = atoi(mReply->str);//::strtoul(mReply->str, NULL, 10);
			}
			break;
		default:
			freeReplyObject(mReply);
			mReply = NULL;
			return false;
		}
		freeReplyObject(mReply);
		mReply = NULL;
	}
	return true;
}

bool RedisConnect::SetLong(const char* key, const long long& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "SET %s %lld", key, value);
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetLong(const char* key, long long& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "GET %s", key);
	if (!mReply)
		return false;
	else
	{
		switch (mReply->type)
		{
		case REDIS_REPLY_INTEGER:
			{
				value = mReply->integer;
			}
			break;
		case REDIS_REPLY_STRING:
			{
				value = ::strtoll(mReply->str, NULL, 10);
			}
			break;
		default:
			freeReplyObject(mReply);
			mReply = NULL;
			return false;
		}
		freeReplyObject(mReply);
		mReply = NULL;
	}
	return true;
}

bool RedisConnect::SetStr(const char* key, const char* value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "SET %s %s", key, value);
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetStr(const char* key, std::string& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "GET %s", key);
	if (!mReply)
		return false;
	else if (mReply->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}

	value.append(mReply->str);
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::SetBin(const char *key, const char* value, int len)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "SET %s %b", key, value, len);
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetBin(const char *key, std::string &value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "GET %s", key);
	if (!mReply)
		return false;
	else if (mReply->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}

	value.resize(mReply->len + 1);
	memcpy(&(*value.begin()), mReply->str, mReply->len);
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::SetHset(const char* key, const char* field, const char* value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "HSET %s %s %s", key, value, value);
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetHset(const char* key, const char* field, std::string& value)
{
	if (!mContext)
		return false;
	mReply = (redisReply*)redisCommand(mContext, "HGET %s %s", key, field);
	if (!mReply)
		return false;
	else if (mReply->type != REDIS_REPLY_STRING)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}

// 	value.resize(mReply->len + 1);
// 	memcpy(&(*value.begin()), (const void *)(mReply->str), mReply->len);
	value.append(mReply->str);
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::SetHMset(const char* key, std::map<std::string, std::string> fieldValue)
{
	if (!mContext)
		return false;
	std::ostringstream redisCmd;
	redisCmd << "HMSET " << key;
	for (auto it : fieldValue)//同for (auto it = fieldValue.begin(); it != fieldValue.end(); ++it)
		redisCmd << " " << it.first << " " << it.second;
	mReply = (redisReply*)redisCommand(mContext, redisCmd.str().c_str());
	if (!mReply)
		return false;

	if (mReply->type == REDIS_REPLY_ERROR)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}

bool RedisConnect::GetHMset(const char* key, const std::set<std::string>& fieldSet, std::map<std::string, std::string>& fieldValue)
{
	if (!mContext)
		return false;
	std::ostringstream redisCmd;
	redisCmd << "HMSET " << key;
	for (auto it : fieldSet)
	{
		fieldValue.insert(std::make_pair(it, ""));
	}
	for (auto it : fieldValue)
	{
		redisCmd << " " << it.first;
	}
	mReply = (redisReply*)redisCommand(mContext, redisCmd.str().c_str());
	if (!mReply)
		return false;
	else if (mReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(mReply);
		mReply = NULL;
		return false;
	}
	int i = 0;
	for (auto it : fieldValue)
	{
		if (i >= mReply->elements)
			break;
		if (mReply->element[i]->str != NULL)
			it.second = mReply->element[i]->str;
		++i;
	}

	freeReplyObject(mReply);
	mReply = NULL;
	return true;
}