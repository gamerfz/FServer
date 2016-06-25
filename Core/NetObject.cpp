#include "NetObject.h"


NetObject::NetObject(NetWork* net, int fd, bufferevent* bev, int tid)
{
	mNetWork = net;
	mFD = fd;
	mEvBuf = bev;
	mTID = tid;
	mIndex = -1;
	mConnected = false;
	mDetect = true;
	//mIP = ((sockaddr_in *)addr)->sin_addr.s_addr;
}

NetObject::~NetObject()
{
}