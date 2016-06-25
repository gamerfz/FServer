#pragma once
#include <Singleton.h>
#include "ConfigManager.h"
#include <glog/glog.h>

class RobotApp : public Singleton<RobotApp>
{
public:
	RobotApp();
	~RobotApp();

private:

};
