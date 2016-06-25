/***********************************************************************
*FileName	:  NetIO
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络IO线程
************************************************************************/
#pragma once
#include <event.h>
#include "NetEventQueue.h"

class NetWork;

class NetIO
{
	event_base* mEvBase;
	/*线程ID 由于thread::id是一个类,不太好,所以单独定义一个的索引ID*/
	int mTID;
	/*接受连接的队列*/
	EventQueue* mConnectQueue;
	/*接收消息的队列*/
	EventQueue* mInputQueue;
	/*发送消息的队列*/
	EventQueue* mOutputQueue;
public:
	NetIO();
	~NetIO();

	bool Init(NetWork* net, int tid);
	void Run();
	void Stop();
	bool IsValid() { return mTID >= 0; }
	event_base* GetEvBase() { return mEvBase; }
	int GetTID() { return mTID; }
	//以下3个事件队列指针是给netIstance调用的,用于将数据添加到队列做处理,比如接收处理消息
	EventQueue* GetInputQueue() { return mInputQueue; }
	EventQueue* GetOutputQueue() { return mOutputQueue; }
	EventQueue* GetConnectQueue() { return mConnectQueue; }
};

