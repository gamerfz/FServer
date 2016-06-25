/***********************************************************************
*FileName	:  BaseSession
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络会话基类,server和client的会话用的都是此基类
************************************************************************/
#pragma once
#include <glog/glog.h>

struct NetMessage;

class BaseSession
{
	/*连接的FD*/
	int mFD;
	/*会话索引 可以理解为一个会话ID*/
	int mIndex;
	/*由于session本身并没有保存任何NetWork或NetInterface指针信息,如果需要session发送消息的接口,可以继承后在逻辑层自己实现,调用底层接口*/
public:
	BaseSession():mFD(-1), mIndex(-1){};
	virtual ~BaseSession(){};

	/*已建立连接*/
	virtual void Connected() = 0;
	/*已断开连接*/
	virtual void Disconnected() = 0;
	/*收消息*/
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0) = 0;

	void SetFD(int fd) { mFD = fd; }
	void SetIndex(int index){ mIndex = index; }
	int GetFD() const { return mFD; }
	int GetIndex() const { return mIndex; }
	bool IsAttach() const { return mIndex >= 0; }
};
