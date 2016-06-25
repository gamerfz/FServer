/***********************************************************************
*FileName	:  NetObject
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络连接对象
************************************************************************/
#pragma once
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event_compat.h>
class NetWork;

class NetObject
{
	NetWork* mNetWork;
	int mFD;
	bufferevent* mEvBuf;
	int mTID;//所在IO线程的ID
	//unsigned int mIP;//IP
	/*连接索引 见NetInterface的mIndex,只是为了提高效率,避免去找session,同时可以作为一种连接状态,确定是否和session绑定*/
	int mIndex;
	/*是否已连接的标志位*/
	bool mConnected;
	/*是否检测心跳 只对监听端有效,默认监听到的连接都需要检测心跳,如不需要检测,由逻辑层自行决定关闭心跳检测*/
	bool mDetect;
public:
	NetObject(NetWork* net, int fd, bufferevent* bev, int tid) :
		mNetWork(net), mFD(fd), mEvBuf(bev), mTID(tid), mIndex(-1), mConnected(false), mDetect(false){}
	~NetObject(){};

	void SetIndex(int index){ mIndex = index; }
	void SetConnected(bool flag) { mConnected = flag; }
	void SetDetect(bool detect) { mDetect = detect; }

	NetWork* GetNetWork() const { return mNetWork; }
	bufferevent* GetEvBuf() const { return mEvBuf; }
	int GetTID() const { return mTID; }
	int GetFD()const { return mFD; }
	int GetIndex() const { return mIndex; }
	bool IsConnected() const { return mConnected; }
	bool IsDetect() const { return mDetect; }
};
