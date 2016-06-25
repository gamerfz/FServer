/***********************************************************************
*FileName	:  NetDefine
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络数据定义
************************************************************************/
#pragma once
#include <glog/glog.h>

/*网络连接*/
struct NetConnect
{
	evutil_socket_t mFD;
	sockaddr_in mAddr;
	unsigned int mIP;
	int mPort;
	bool mCaller;//是否连接发起者 true:Client false:Server
};
/*网络包事件类型*/
enum NetPacketEvent
{
	ENPE_Connected		= 1,	
	ENPE_Disconnect		= 2,
	ENPE_Read			= 3,
	ENPE_Write			= 4,
	ENPE_Broadcast		= 5,
};

/*网络包 服务端内部组的包*/
struct NetPacket
{
	NetPacketEvent mEvent;	//包事件类型
	int mFD;				//socket的fd
	int mIndex;				//
	char mBody[1];			//带包头(消息长度)的完整数据
};
/*网络包基础长度,除NetPacket的mBody*/
#define NET_PACKET_BASE_LENGTH	sizeof(NetPacketEvent)+sizeof(int)+sizeof(int)

/*网络消息 原始数据,NetPacket的mBody*/
struct NetMessage
{
	int mLength;	//消息长度 实际NetMessage的长度
	char mMsg[0];	//消息体 零长可变长度数组：用于结构体的末尾,本身不占用空间,因此对sizeof没有影响,如果有点编译器不支持,可以换成1长数组  
};
/*消息头的长度 NetMessage的mLength*/
#define MSG_HEAD_LENGTH sizeof(int)	
/*消息最大长度 注意,8*1024是一个建议的合理值,tcp不建议发送过大的数据,以免在网络拥堵或丢包重发的情况下造成更大的延迟,实际代码中这个值可以设的很大,甚至可以接收一些流或文件等大数据,但还是应该做一些限制,尽量用拆包的方式去处理*/
#define MSG_MAX_LENGTH 8*1024
/*网络超时秒数 服务端检测为2倍的时间*/
#define NET_TIMEOUT_SECONDS 10