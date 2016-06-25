/***********************************************************************
*FileName	:  EventQueue
*Author		:  fz
*Date		:  2016.1.17
*Description:  网络事件队列
************************************************************************/
#pragma once
#include <functional>
#include <mutex>
#include <event.h>
#include <event2/event_struct.h>

/*处理事件的回调 function<返回类型(回调函数, 回调函数参数)>*/
typedef std::function<void(void* msg, void* args)> OnEventCB;

typedef void* Elem;
struct CircleBuffer
{
	int m_head;
	int m_tail;
	int m_curCount;
	int m_maxCount;
	Elem m_elems[1];
};

//网络消息事件队列
class EventQueue
{
	/*环形队列*/
	CircleBuffer* mQueue;
	//利用evutil_socketpair实现一对匿名读写socket,当向写socket写入数据时,读socket就会得到通知,触发读事件
	/*写socket*/
	evutil_socket_t mWriteFD;
	/*读socket*/
	evutil_socket_t mReadFD;
	event mEvent;
	std::mutex mLock;
	/*上层处理事件的回调函数*/
	OnEventCB mEventCB;
	/*上层处理事件的回调函数参数*/
	void* mEventCBArgs;
public:
	EventQueue(OnEventCB eventCB, void* eventCBArgs, int maxSize);
	~EventQueue();

	bool InitQueue(event_base* evBase);
	bool ClearQueue();

	CircleBuffer* GetQueue() { return mQueue; }
	//添加到事件队列
	bool PushToQueue(void* netEvent);

private:
	//socket_pair_write
	int SocketWrite(){ return send(mWriteFD, "", 1, 0); }
	//socket_pair_read
	void SocketRead()
	{
		unsigned char buf[1024];
		while (recv(mReadFD, (char*)buf, sizeof(buf), 0) > 0){}
	}
	//处理并移除事件,根据事先注册好的事件回调函数处理队列中的事件
	static void PopToQueue(evutil_socket_t fd, short events, void* args);
};
