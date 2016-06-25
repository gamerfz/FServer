#pragma once
#include "BaseCenterApp.h"
#ifdef WIN32
#include "WinDump.h"
#endif

int main(int argc, char* argv[])
{
#ifdef WIN32
	WinDump wDump("BaseCenterApp");
#endif
	if (!theConfigMgr->ParseCommond(argc, argv))
		return false;

	FLAGS_max_log_size = 100;/*log文件大小MB*/
	FLAGS_stop_logging_if_full_disk = false;/*避免写日志磁盘已满*/ // 暂不避免
	FLAGS_logbufsecs = 0;/*实时输出*/
	FLAGS_colorlogtostderr = true;
	google::InitGoogleLogging("");
	google::SetLogDestination(google::GLOG_ERROR, "./Log/Error");
	google::SetLogDestination(google::GLOG_INFO, "./Log/Info");
	google::SetStderrLogging(google::GLOG_INFO);
	std::stringstream ss;
	ss << "BaseCenterApp" << theConfigMgr->GetAppID() << "-";
	google::SetLogFilenameExtension(ss.str().c_str());//设置文件名扩展	

	LOG(INFO) << "info test";
	LOG(ERROR) << "error test";

	if (theBaseCenterApp->Init())
		theBaseCenterApp->StartUp();
	theBaseCenterApp->ShutDown();

	return 0;
}