/************************************************************************
*	@brief		：	Windows下生成Dump文件
*	@author		：	
*	@date		：	2015-5
************************************************************************/
#pragma once
#ifdef WIN32//_MSC_VER//WIN32
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <DbgHelp.h>

using namespace std;

class WinDump
{
public:
	/* 目录文件需要预先创建,默认为执行文件同级目录,实际文件命由file+时间等基本信息组成,详细见ExceptionFilter */
	WinDump(char * file, char * dir = "./");
	~WinDump();

	static LONG WINAPI					ExceptionFilter( struct _EXCEPTION_POINTERS * pExceptionInfo );
	static std::stringstream			m_fileDir;
	static std::stringstream			m_fileName;
};

#endif

