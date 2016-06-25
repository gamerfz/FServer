#include "NetEventQueue.h"
#include <glog/glog.h>

CircleBuffer* CBufferNew(unsigned int maxCount)
{
	if (maxCount == 0)
		return NULL;
	CircleBuffer* cBuf = (CircleBuffer*)calloc(1, sizeof(CircleBuffer)+sizeof(Elem)*maxCount - 1);//-1是因为CircleBuffer包括的Elem部分
	if (cBuf == NULL)
		return NULL;
	cBuf->m_head = 0;
	cBuf->m_tail = 0;
	cBuf->m_curCount = 0;
	cBuf->m_maxCount = maxCount;
	return cBuf;
}
static void CBufferFree(CircleBuffer* cBuf)
{
	free(cBuf);
}
//如果满了，将cBuf清空
static inline void CBufferClear(CircleBuffer* cBuf)
{
	cBuf->m_head = 0;
	cBuf->m_tail = 0;
	cBuf->m_curCount = 0;
}
static bool CBufferPush(CircleBuffer* cBuf, const Elem em)
{
	if (cBuf->m_curCount >= cBuf->m_maxCount) //buf已满是否需要清除重置还是将em另外处理交由上层自行处理
		return false;
	cBuf->m_elems[cBuf->m_tail++] = em;
	if (cBuf->m_tail >= cBuf->m_maxCount)
		cBuf->m_tail = 0;
	++cBuf->m_curCount;
	return true;
}
static Elem CBufferPop(CircleBuffer* cBuf)
{
	if (cBuf->m_curCount == 0)
		return NULL;
	Elem em = cBuf->m_elems[cBuf->m_head++];
	if (cBuf->m_head >= cBuf->m_maxCount)
		cBuf->m_head = 0;
	--cBuf->m_curCount;
	return em;
}
static inline unsigned int CBufferSize(CircleBuffer* cq)
{
	return cq->m_curCount;
}
static inline bool CBufferIsEmpty(CircleBuffer* cBuf)
{
	return cBuf->m_curCount == 0;
}
static inline bool CBufferIsFull(CircleBuffer* cBuf)
{
	return cBuf->m_curCount >= cBuf->m_maxCount;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

EventQueue::EventQueue(OnEventCB eventCB, void* eventCBArgs, int maxSize)
{
	mQueue = NULL;
	mWriteFD = -1;
	mReadFD = -1;
	mEventCB = eventCB;
	mEventCBArgs = eventCBArgs;
	mQueue = CBufferNew(maxSize);
}

EventQueue::~EventQueue()
{
}

bool EventQueue::InitQueue(event_base* evBase)
{
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
		return false;

	mWriteFD = fds[0];
	mReadFD = fds[1];
	evutil_make_socket_nonblocking(mWriteFD);
	evutil_make_socket_nonblocking(mReadFD);
	event_assign(&mEvent, evBase, mReadFD, EV_READ | EV_PERSIST, PopToQueue, this);
	event_add(&mEvent, NULL);
	return true;
}

bool EventQueue::ClearQueue()
{
	if (mQueue)
	{
		CBufferFree(mQueue);
		mQueue = NULL;
	}
	event_del(&mEvent);
	if (mReadFD != -1) 
	{
		evutil_closesocket(mReadFD);
		mReadFD = -1;
	}
	if (mWriteFD != -1) 
	{
		evutil_closesocket(mWriteFD);
		mWriteFD = -1;
	}
	return true;
}

bool EventQueue::PushToQueue(void* netEvent)
{
	mLock.lock();
	if (CBufferIsFull(mQueue))
	{
		LOG(ERROR) << "MsgQueue is full! " << LogValue("size", CBufferSize(mQueue));
		CBufferClear(mQueue);
	}
	if (!CBufferPush(mQueue, netEvent))
	{
		mLock.unlock();
		return false;
	}
	if (CBufferSize(mQueue) == 1)
		SocketWrite();
	mLock.unlock();
	return true;
}

void EventQueue::PopToQueue(evutil_socket_t fd, short events, void* args)
{
	auto eq = (EventQueue*)args;
	eq->SocketRead();
	eq->mLock.lock();
	while (CBufferSize(eq->GetQueue()) >= 1)
	{
		auto netEvent = CBufferPop(eq->GetQueue());
		eq->mEventCB(netEvent, eq->mEventCBArgs);
		//可以在此处写个log来查看实际情况下每个IO一次到底处理了多少逻辑,主要是逻辑线程,在考虑要不要改
	}
	eq->mLock.unlock();
}

/*
bool EventQueue::SocketInit(event_base* evBase, event_callback_fn fn, void* args)
{
evutil_socket_t fds[2];
if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
return false;

mWriteFD = fds[0];
mReadFD = fds[1];
evutil_make_socket_nonblocking(mWriteFD);
evutil_make_socket_nonblocking(mReadFD);
//event_assign将mReadFD作为触发事件的内部fd,并将回调关联到fn回调函数,利用了IO的底层实现,所有的事件的响应都会回调到fn这个函数
event_assign(&mEvent, evBase, mReadFD, EV_READ | EV_PERSIST, fn, args);
event_add(&mEvent, NULL);
/ *流程是这样的：evsig_add作为入口函数，其调用流程将某个linux信号通过sigaction或signal关联到evsig_handler这个回调函数，
在回调函数的内部将信号量作为数据写到socketpair[0]，发送给另一端。另一端通过 socketpair[1]读取到信号后，
回调保存在 base->sig.ev_signal 中的回调函数，即 evsig_cb.在这个函数的内部，完成了将事件通知到上层，
到这时候，其实现与IO的事件触发完全一样了。* /

return true;
}
*/
