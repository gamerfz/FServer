#include "WinDump.h"

stringstream WinDump::m_fileDir;
stringstream WinDump::m_fileName;

WinDump::WinDump(char * file, char * dir /* = "./Dump" */)
{
	m_fileDir << dir;
	m_fileName << file;
	SetUnhandledExceptionFilter(ExceptionFilter); 
}

WinDump::~WinDump()
{

}

LONG WINAPI WinDump::ExceptionFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)  
{
	struct tm * nt;
	time_t		ltime;
	time( &ltime );
	nt = localtime( &ltime );

	std::stringstream fn;

	fn << m_fileDir.str().data() << "\\" << m_fileName.str().data() << (nt->tm_year+1900)
		<< nt->tm_mon+1 << nt->tm_mday << "_" << nt->tm_hour << nt->tm_min <<  nt->tm_sec << ".dmp";

	HANDLE hFile = CreateFileA(fn.str().data(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
	MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;  
	stExceptionParam.ThreadId			= GetCurrentThreadId();  
	stExceptionParam.ExceptionPointers	= pExceptionInfo;  
	stExceptionParam.ClientPointers		= FALSE;  
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &stExceptionParam, NULL, NULL);  
	CloseHandle(hFile);  
	getchar();
	return EXCEPTION_EXECUTE_HANDLER;
}

