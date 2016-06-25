#include "windows.h"
#include "shellapi.h"
#include "string"
#include <sstream>
#include <vector>

DWORD shell(const char* cmdline)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	GetStartupInfo(&si);

	std::string a = cmdline;
	std::wstring widstr = std::wstring(a.begin(), a.end());
	LPWSTR str = (LPWSTR)widstr.c_str();

	CreateProcess(NULL,
		str,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi
		);
	return pi.dwProcessId;
}

int main(int argc, char* argv[])
{
	std::string command = "Robot.exe";
	char* ipaddress = argv[1];
	char* port = argv[2];
	char* username = argv[3];

	command = command + " " + ipaddress + " " + port + " " + username;
	int startnumber = atoi(argv[4]);
	int number = atoi(argv[5]);
	for (int i = 1; i <= number; ++i)
	{
		std::string realcommand = command;
		std::stringstream stream;
		stream << startnumber;
		realcommand = realcommand + stream.str();
		shell(realcommand.c_str());
		Sleep(500);
		++startnumber;
	}
}

