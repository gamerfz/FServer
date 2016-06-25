#include <glog/glog.h>
#include "DBInterface.h"

DBInterface::DBInterface()
{
}

DBInterface::~DBInterface()
{
}

void DBInterface::Init(const std::string& name, const std::string& user, const std::string& password, const std::string& host, unsigned int port)
{
	m_name = name;
	m_user = user;
	m_password = password;
	m_host = host;
	m_port = port;
}

bool DBInterface::Connect()
{
	try
	{
		m_connection.set_option(new mysqlpp::SetCharsetNameOption("utf8"));
		if (!m_connection.connect(m_name.c_str(), m_host.c_str(), m_user.c_str(), m_password.c_str(), m_port))
		{
			LOG(ERROR) << "Mysql connect failed!";
			return false;
		}
	}
	catch (mysqlpp::Exception& e)
	{
		LOG(ERROR) << "Mysql connect failed!" << LogValue("Error", e.what());
		return false;
	}
	catch (...)
	{
		LOG(ERROR) << "Mysql connect failed! Unknown error!!";
		return false;
	}

	LOG(INFO) << "Mysql connect success!";
	return true;
}

void DBInterface::DisConnect()
{
	m_connection.disconnect();
}

bool DBInterface::ReConnect(int count /* = 0 */)
{
	DisConnect();
	if (Connect())
	{
		#if defined(WIN32) && !defined(DEV_WIN32)
			Sleep(1);
		#else
			usleep(1000);
		#endif
		LOG(INFO) << "Mysql reconnect success!";
		return true;
	}
	else
	{
		#if defined(WIN32) && !defined(DEV_WIN32)
			Sleep(1);
		#else
			usleep(1000);
		#endif
		if (count <= 0)
		{
			LOG(ERROR) << "Mysql reconnect failed!";
			return false;
		}	
		else
			return ReConnect(count--);
	}
}

bool DBInterface::SqlExcute(const char* sql, SqlParams& sqlParams, SqlResult& sqlResult)
{
	try
	{
		mysqlpp::Query mysqlQuery = m_connection.query();
		mysqlQuery << sql;
		mysqlQuery.parse();
		sqlResult = mysqlQuery.store(sqlParams);
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG(ERROR) << "DBStoreT failed! BadQuery!!" << LogValue("ErrorType", errCode) << LogValue("Error", er.what()) << LogValue("Sql", sql);

		if (errCode == 2013 || errCode == 2006)
		{
			if (!ReConnect(RECONNECT_COUNT))
			{
				LOG(ERROR) << "Could not reconnect to MySQL!!! Closing Process!" << LogValue("ErrorCode", errCode) << LogValue("Sql", sql);
				#if WIN32
					ExitProcess(0);
				#else
					exit(0);
				#endif
				return false;
			}
			else
				return SqlExcute(sql, sqlParams, sqlResult);//,当mysql重连成功后又马上断开,SQL操作失败,将继续重连,此时极端情况逻辑会出现死循环
		}
		else
		{
			return false;
		}

	}
	catch (const mysqlpp::BadConversion& er)
	{
		LOG(ERROR) << "DBStoreT failed! BadConversion!!" 
			<< LogValue("Error", er.what()) << LogValue("Sql", sql) 
			<< LogValue("dataSize", er.retrieved) << LogValue("actualSize", er.actual_size);
		return false;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Error", er.what()) << LogValue("Sql", sql);
		return false;
	}
	catch (std::exception &er)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Error", er.what()) << LogValue("Sql", sql);
		return false;
	}
	catch (...)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Sql", sql);
		return false;
	}
	return true;
}

bool DBInterface::SqlExcute(const char* sql, SqlParams& sqlParams, SqlExcuteResult& sqlResult)
{
	try
	{
		mysqlpp::Query mysqlQuery = m_connection.query();
		mysqlQuery << sql;
		mysqlQuery.parse();
		sqlResult = mysqlQuery.execute(sqlParams);
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG(ERROR) << "DBStoreT failed! BadQuery!!" 
			<< LogValue("ErrorType", errCode) << LogValue("Error", er.what()) << LogValue("Sql", sql);

		if (errCode == 2013 || errCode == 2006)
		{
			if (!ReConnect(RECONNECT_COUNT))
			{
				LOG(ERROR) << "Could not reconnect to MySQL!!! Closing Process!" 
					<< LogValue("ErrorCode", errCode) << LogValue("Sql", sql);
				#if WIN32
					ExitProcess(0);
				#else
					exit(0);
				#endif
				return false;
			}
			else
				return SqlExcute(sql, sqlParams, sqlResult);//当mysql重连成功后又马上断开,SQL操作失败,将继续重连,此时极端情况逻辑会出现死循环
		}
		else
		{
			return false;
		}

	}
	catch (const mysqlpp::BadConversion& er)
	{
		LOG(ERROR) << "DBStoreT failed! BadConversion!!" 
			<< LogValue("Error", er.what()) << LogValue("Sql", sql) 
			<< LogValue("dataSize", er.retrieved) << LogValue("actualSize", er.actual_size);
		return false;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Error", er.what()) << LogValue("Sql", sql);
		return false;
	}
	catch (std::exception &er)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Error", er.what()) << LogValue("Sql", sql);
		return false;
	}
	catch (...)
	{
		LOG(ERROR) << "DBStoreT failed!" << LogValue("Sql", sql);
		return false;
	}
	return true;
}