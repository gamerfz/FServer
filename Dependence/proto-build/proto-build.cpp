// proto-build.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/stubs/common.h>

void CompileAllProtoFile(google::protobuf::internal::scoped_array<const char*>& param, google::protobuf::compiler::CommandLineInterface& cli)
{
	char szFile[_MAX_PATH + 1] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "*.proto");

	WIN32_FIND_DATA xFindData;
	HANDLE hFile = FindFirstFile(szFile, &xFindData);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			char szFileName[_MAX_PATH];
			sprintf_s(szFileName, _MAX_PATH - 1, "%s", xFindData.cFileName);
			param[2] = szFileName;

			int nResult = cli.Run(3, param.get());
			if (nResult == 0)
			{
				std::cout << nResult << " : 编译 [" << xFindData.cFileName << " ] 完成!" << std::endl;
			}
			else
			{
				std::cout << nResult << " : 编译 [" << xFindData.cFileName << " ] 失败!" << std::endl;
			}

		} while (FindNextFile(hFile, &xFindData));
		FindClose(hFile);
	}
}

void CompileProtoFile(std::string& strFile, google::protobuf::internal::scoped_array<const char*>& param, google::protobuf::compiler::CommandLineInterface& cli)
{
	char szFileName[_MAX_PATH];
	sprintf_s(szFileName, _MAX_PATH - 1, "%s", strFile.c_str());
	param[2] = szFileName;

	int nResult = cli.Run(3, param.get());
	if (nResult == 0)
	{
		std::cout << nResult << " : 编译 [" << strFile.c_str() << " ] 完成!" << std::endl;
	}
	else
	{
		std::cout << nResult << " : 编译 [" << strFile.c_str() << " ] 失败!" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	google::protobuf::internal::scoped_array<const char*> param(new const char*[3]);
	param[0] = "-I=.";
	param[1] = "--cpp_out=.";//输出目录

	google::protobuf::compiler::CommandLineInterface cli;
	cli.AllowPlugins("protoc-");

	google::protobuf::compiler::cpp::CppGenerator cpp_generator;
	cli.RegisterGenerator("--cpp_out", &cpp_generator,
		"Generate C++ header and source.");


	std::cout << "**********************************************************\r\n";
	std::cout << "                        说明\r\n";
	std::cout << "   请输入编译的proto文件名(*为编译所有文件)\r\n";
	std::cout << "**********************************************************\r\n";

	std::string strCommand;
	while (true)
	{
		std::cout << ">>";
		std::cin >> strCommand;
		if (strCommand.compare("exit") == 0)
		{
			break;
		}

		strCommand += ".proto";
		if (strCommand == "*.proto")
		{
			CompileAllProtoFile(param, cli);
		}
		else
		{
			CompileProtoFile(strCommand, param, cli);
		}
	}

	return 0;
}

