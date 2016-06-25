/***********************************************************************
*FileName	:  NetInterface
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络接口(网络层供逻辑层调用的一个接口,可以理解为一个网络和逻辑之间的中间层)
************************************************************************/
#pragma once
#include <vector>
#include <google/protobuf/message.h>
#include "BaseSession.h"
#include "NetWork.h"

class NetInterface
{
	NetWork* mNetWork;
	std::vector<BaseSession*> mvecSession;
public:
	NetInterface();
	virtual~NetInterface();

	/*初始网络 Server (端口, 单个线程中的连接数, 线程数)*/
	bool Init(int port, int connCnt, int ioCnt = 4);
	
	/*发起连接 Client (目标IP, 目标端口) 操作成功返回底层FD用于添加session*/
	evutil_socket_t OnConnectTo(const std::string& ip, int port);
	/*OnConnectTo成功后网络层的回调 由逻辑层自己决定是否绑定session,外部建立的连接可以通过OnMessage自行处理*/
	virtual void OnConnected(const NetPacket& msg){};

	/*处理收到的消息 这里只是处理有session的消息,未添加或不需要添加session的消息可以继承后重写此函数*/
	virtual void OnMessage(const NetPacket& msg, int msgType = 0);
	/*处理发送的消息 应该多用传session的方式,只有在无session的时候才用fd*/
	virtual bool OnSend(BaseSession* session, ::google::protobuf::Message* pbMsg);
	virtual bool OnSend(int fd, ::google::protobuf::Message* pbMsg);
	virtual bool OnSendToAll(::google::protobuf::Message* pbMsg);

	/*断开连接*/
	bool OnDisconnect(int index);
	bool OnDisconnectByFD(int fd);
	
	/*连接/解除session 其中连接分监听(listen)和主动请求(connect)*/
	bool AttachSession(BaseSession* session);
	void RemoveSession(BaseSession* session);

	NetWork* GetNetWork() const { return mNetWork; }
	NetObject* GetNetObject(BaseSession* session);
	BaseSession* GetSession(int index);
	BaseSession* GetSessionByFD(int fd);
private:
	/*处理网络事件 由网络层取出事件处理或转发逻辑层*/
	int OnNetEvent(const NetPacket& msg);

	/*组建发送的包*/
	NetPacket* BuildOutPacket(BaseSession* session, ::google::protobuf::Message* pbMsg);
	NetPacket* BuildOutPacket(int fd, ::google::protobuf::Message* pbMsg);
	NetPacket* BuildBroadcastPacket(::google::protobuf::Message* pbMsg);

	/*向网络层发送消息的接口 见OnSend处理*/
	bool SendPacket(NetPacket* packet);
	bool SendPacketToAll(NetPacket* packet);
};
