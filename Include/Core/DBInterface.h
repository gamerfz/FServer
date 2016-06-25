/***********************************************************************
*FileName	:  DBInterface
*Author		:  fz
*Date		:  2016.1.13
*Description:  mysqlpp的封装类,直接继承即可
************************************************************************/
#pragma once
#include <string>
#include <mysql++.h>

typedef mysqlpp::SQLQueryParms    SqlParams;
typedef mysqlpp::SQLTypeAdapter   SqlType;
typedef mysqlpp::StoreQueryResult SqlResult;		// select
typedef mysqlpp::SimpleResult	  SqlExcuteResult;	// update delete insert
typedef mysqlpp::Row              SqlRow;
typedef mysqlpp::sql_int_unsigned SqlUInt32;
typedef mysqlpp::sql_bigint_unsigned SqlBigInt;

#define RECONNECT_COUNT 10	//重连数据库的次数,重连间隔为1毫秒

/*数据库实例基础类*/
class DBInterface
{
	std::string m_name;					//数据库名
	std::string m_user;					//登录的用户名
	std::string m_password;				//登录的密码
	std::string m_host;					//数据库地址
	unsigned int m_port;				//数据库端口
	mysqlpp::Connection m_connection;	//数据库连接
public:
	DBInterface();
	virtual~DBInterface();

	/*初始化数据库基础数据*/
	void Init(const std::string& name, const std::string& user, const std::string& password, const std::string& host, unsigned int port);
	/*连接数据库*/
	bool Connect();
	/*断开数据库连接*/
	void DisConnect();
	/*断线重连*/
	bool ReConnect(int count = 0);
	/*SQL操作*/
	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlResult& sqlResult);//SELECT
	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlExcuteResult& sqlResult);//INSERT UPDATE DELETE
	
};
