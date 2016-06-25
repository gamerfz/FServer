/***********************************************************************
*FileName	:  NetWork
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络实例(网络核心)
************************************************************************/
#pragma once
#include <map>
#include <vector>
#include <thread>
#include <memory>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/thread.h>
#include <event2/event_compat.h>
#include "NetDefine.h"
#include "NetListener.h"
#include "NetIO.h"
#include "NetObject.h"

typedef std::function<int(const NetPacket& msg)> OnNetCB;
typedef std::shared_ptr<OnNetCB> OnNetCBPtr;

class NetWork
{
	event_base*	mEvBase;
	/*监听线程*/
	NetListener* mListener;
	/*网络监听的端口*/
	int mPort;
	/*单个IO线程最大连接数*/
	int mConnectCount;
	/*IO线程数*/
	int mIOCount;
	/*用于调度IO线程*/
	int mCurIOIndex;
	/*IO线程列表*/
	std::vector<NetIO*> mvecNetIO;
	/*连接对象map<fd,obj> 效率考虑可以改成vector或unorder_map*/
	std::map<int, NetObject*> mmapObject;
	/*上层处理网络事件的回调函数*/
	OnNetCB mOnNetCB;
public:
	template<typename Entity>
	NetWork(Entity* entity, int (Entity::*OnNet)(const NetPacket&), int port, int connCnt, int ioCnt = 4)
	{
		mEvBase = NULL;
		mListener = NULL;
		mPort = port;
		mConnectCount = connCnt;
		mIOCount = ioCnt;
		mOnNetCB = std::bind(OnNet, entity, std::placeholders::_1);
	}
	virtual ~NetWork(){};
	
	virtual bool CreateNet();
	virtual bool StartNet();
	virtual bool CloseNet();

	/*主动发起连接 相当于client,但必须先CreateNet,连接成功也会进入IO线程的队列*/
	virtual evutil_socket_t ConnectTo(const std::string& ip, int port);

	/*网络事件回调函数 分别针对网络连接和数据的收发,详细见OnEventCB*/
	virtual void OnConnectEvent(void* msg, void* args);
	virtual void OnInputEvent(void* msg, void* args);
	virtual void OnOutputEvent(void* msg, void* args);

	/*上层调用发数据的接口*/
	virtual bool SendData(NetPacket* packet);

	virtual bool AddNetObject(const int fd, NetObject* obj){ return mmapObject.insert(std::make_pair(fd, obj)).second; }
	virtual bool RemoveNetObject(const int fd);

	/*线程调度 只是简单的轮换,高级的规则可以自己重写*/
	virtual NetIO* DispatchIO();

	bool SetEvBufferTimeout(int fd, int sec);

	event_base* GetEvBase() const { return mEvBase; }
	int GetPort() const { return mPort; }
	int GetMaxConnect() const { return mIOCount * mConnectCount; }
	bool CheckConnectFull(){ return mmapObject.size() >= GetMaxConnect(); }
	NetIO* GetNetIO(int tid);
	NetObject* GetNetObject(int fd);
private:
	/*libevent发送的接口 由于未经过网络层的事件队列 上层不应该直接调用以下Send函数,应该通过SendData进入相应的IO消息队列在做处理*/
	virtual bool Send(const char* msg, const int len, const int fd);
	virtual bool SendToAll(const char* msg, const int len);

	/*libevent处理读写和底层事件的回调*/
	static void conn_readcb(bufferevent* evBuf, void* uData);
	static void conn_writecb(bufferevent* evBuf, void* uData);
	static void conn_eventcb(bufferevent* evBuf, short events, void* uData);
};
