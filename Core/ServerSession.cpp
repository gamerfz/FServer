#include "ServerSession.h"

ConnectEvent::ConnectEvent(NetInterface* nif, ServerSession* session, const std::string& ip, int port, int msec) :
TimerEvent(nif->GetNetWork()->GetEvBase(), msec, false),
mNetInterface(nif),
mSession(session),
mstrIP(ip),
mPort(port),
mSSStatus(ESSS_Default)
{
}

ConnectEvent::~ConnectEvent()
{
}

void ConnectEvent::OnTimer()
{
	if (!mSession)
	{
		LOG(ERROR) << "Unknown ServerSession!" << LogValue("ip", mstrIP) << LogValue("port", mPort);
		return;
	}
	switch (mSSStatus)
	{
	case ESSS_Default:
		{
			if (mSession->GetIndex() == -1)//只attach没有确定index的session
			{
				if (!mNetInterface->AttachSession(mSession))//attach失败重置定时器等下次处理
				{
					ResetTimer(this);
					break;
				}
			}
			mSession->SetFD(mNetInterface->OnConnectTo(mstrIP, mPort));//连接并设置fd,失败为-1
			auto obj = mNetInterface->GetNetObject(mSession);
			if (obj)
			{
				obj->SetIndex(mSession->GetIndex());//绑定或重新绑定底层obj
				mSSStatus = ESSS_Connecting;
			}		
			ResetTimer(this);
		}
		break;
	case ESSS_Connecting:
		{
			auto obj = mNetInterface->GetNetObject(mSession);
			if (obj)
			{
				if (obj->IsConnected())
				{
					LOG(INFO) << "ServerSession Connected!" << LogValue("ip", mstrIP) << LogValue("port", mPort);
					mSSStatus = ESSS_Connected;
					//ResetTimer(this);
					RemoveTimer(this);
					break;
				}
			}
			else//连接失败,底层obj已删除,重新连接
			{
				mSSStatus = ESSS_Default;
				ResetTimer(this);
			}
		}
		break;
	case ESSS_Connected:
		break;
	case ESSS_Final:
		break;
	default:
		break;
	}
}

bool ConnectEvent::Reconnect()
{
	mSSStatus = ESSS_Default;
	return ResetTimer(this);
}

void ConnectEvent::Disconnect()
{
	mSSStatus = ESSS_Final;
	//mNetInterface->RemoveSession(mSession);
	mNetInterface->OnDisconnect(mSession->GetIndex());
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
ServerSession::ServerSession():
mConnectEvent(NULL),
mRepeated(false)
{
}

ServerSession::~ServerSession()
{
	if (mConnectEvent)
	{
		delete mConnectEvent;
		mConnectEvent = NULL;
	}
}

bool ServerSession::Connect(NetInterface* nif, const std::string& ip, int port, int msec, bool repeated /* = true */)
{
	if (!nif)
		return false;
	if (!nif->GetNetWork())
		return false;

	mRepeated = repeated;
	if (!mConnectEvent)
		mConnectEvent = new ConnectEvent(nif, this, ip, port, msec);

	return AddTimer(mConnectEvent);
}
