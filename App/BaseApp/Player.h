/***********************************************************************
*FileName	:  Player
*Author		:  fz
*Date		:  2016.5.21
*Description:  player类,只是继承了网络会话,其他的模块需要另外添加,考虑直接增加脚本调用的接口,另外逻辑主要放在脚本上,也可以C++实现
************************************************************************/
#pragma once
#include <PlayerSession.h>
#include <PoolManager.h>
#include "ProtoMessage.h"


class Player : PlayerSession
{
public:
	Player();
	~Player();

	//void OnReset();//?先不处理,看看kbe怎么处理玩家的对象池重置

	bool SendToClient(::google::protobuf::Message* pbMsg);
	bool SendToBC(::google::protobuf::Message* pbMsg);
	bool SendToGame(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);
};
