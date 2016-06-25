#include "NetIO.h"
#include <thread>
#include "NetWork.h"

NetIO::NetIO()
{
	mEvBase = NULL;
	mTID = -1;
	mInputQueue = NULL;
	mOutputQueue = NULL;
	mConnectQueue = NULL;
}

NetIO::~NetIO()
{
	Stop();
}

bool NetIO::Init(NetWork* net, int tid)
{
	mEvBase = event_base_new();
	if (!mEvBase)
		return false;
	mTID = tid;
	OnEventCB connectEventCB = std::bind(&NetWork::OnConnectEvent, net, std::placeholders::_1, std::placeholders::_2);
	OnEventCB inputEventCB = std::bind(&NetWork::OnInputEvent, net, std::placeholders::_1, std::placeholders::_2);
	OnEventCB outputEventCB = std::bind(&NetWork::OnOutputEvent, net, std::placeholders::_1, std::placeholders::_2);

	mConnectQueue = new EventQueue(connectEventCB, this, 512 * 1024);
	if (!mConnectQueue->InitQueue(mEvBase))
	{
		Stop();
		return false;
	}
	mInputQueue = new EventQueue(inputEventCB, this, 512 * 1024);
	if (!mInputQueue->InitQueue(net->GetEvBase()))
	{
		Stop();
		return false;
	}
	mOutputQueue = new EventQueue(outputEventCB, this, 512 * 1024);
	if (!mOutputQueue->InitQueue(mEvBase))
	{
		Stop();
		return false;
	}

	return true;
}

void NetIO::Stop()
{
	mTID = -1;
	if (mInputQueue)
	{
		mInputQueue->ClearQueue();
		delete mInputQueue;
		mInputQueue = NULL;
	}
	if (mOutputQueue)
	{
		mOutputQueue->ClearQueue();
		delete mOutputQueue;
		mOutputQueue = NULL;
	}
	if (mConnectQueue)
	{
		mConnectQueue->ClearQueue();
		delete mOutputQueue;
		mConnectQueue = NULL;
	}
	if (mEvBase)
	{
		event_base_free(mEvBase);
		mEvBase = NULL;
	}
}

void NetIO::Run()
{
	std::thread(event_base_loop, mEvBase, 0).detach();
}
/*
void Loop::run()
{
//_thread = new std::thread(std::bind(&Loop::run, this));
_frameEvent = event_new(_base, -1, EV_PERSIST, frameEventCallback, this);
if (NULL == _frameEvent)
{
return;
}

struct timeval tv = {};
evutil_timerclear(&tv);
tv.tv_sec = 0;
tv.tv_usec = 5000;

if (0 != event_add(_frameEvent, &tv))
{
event_free(_frameEvent);
_frameEvent = NULL;
return;
}

curThreadLoop = this;
doEvent(ec::Loop::kEventRun);
event_base_loop(_base, 0);
doEvent(ec::Loop::kEventEnd);
curThreadLoop = NULL;
_thread = NULL;
}*/