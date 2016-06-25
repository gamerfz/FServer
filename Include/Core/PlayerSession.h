/***********************************************************************
*FileName	:  PlayerSession
*Author		:  fz
*Date		:  2016.5.21
*Description:  服务端listen的player会话
************************************************************************/
#pragma once
#include <GPDef.h>
#include <BaseSession.h>
#include <PoolManager.h>

/*子类定义的数据需要重写OnReset回收数据*/
class PlayerSession : public BaseSession, public PoolObject
{
public:
	PlayerSession();
	virtual~PlayerSession();

	virtual void OnReset();

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};
