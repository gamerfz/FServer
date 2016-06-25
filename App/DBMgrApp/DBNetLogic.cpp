#include "DBNetLogic.h"
#include "DBMgrApp.h"
#include "ProtoMessage.h"
#include "AppManager.h"

DBNetLogic::DBNetLogic()
{
}

DBNetLogic::~DBNetLogic()
{
}

void DBNetLogic::OnMessage(const NetPacket& packet)
{
	NetMessage* nmsg = (NetMessage*)(packet.mBody);

	auto msgType = theProtoMsgMgr->GetMsgType(nmsg);
#ifdef DEBUG
	LOG(INFO) << "msg " << msgType;
#endif
	switch (msgType)
	{
	case Msg_RegisterApp:
		OnRegisterApp(nmsg, packet.mFD);
		break;
	case Msg_UnRegisterApp:
		OnUnRegisterApp(nmsg);
		break;
	default:
		NetInterface::OnMessage(packet, msgType);
		break;
	}
}

void DBNetLogic::OnRegisterApp(const NetMessage* nmsg, int fd)
{
	MsgRegisterApp msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto app = theAppMgr->AddObject(msg.app_id());
	if (app == NULL)
		return;//有重复的,暂时不断开连接,除非有必要
	
	app->SetFD(fd);
	app->SetAppID(msg.app_id());
	app->SetAppType(msg.app_type());
	AttachSession(app);

	MsgRespondApp res;
	res.mutable_base()->set_type(Msg_RespondApp);
	res.mutable_base()->set_result(1);
	app->SendToApp(&res);

	LOG(INFO) << "RegisterApp" << LogValue("apptype", msg.app_type()) << LogValue("appid", msg.app_id());
}

void DBNetLogic::OnUnRegisterApp(const NetMessage* nmsg)
{
	MsgUnRegisterApp msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto app = theAppMgr->GetObject(msg.app_id());
	if (!app)
		return;
	OnDisconnect(app->GetIndex());
	theAppMgr->RemoveObject(app->GetAppID());

	LOG(INFO) << "UnRegisterApp" << LogValue("apptype", msg.app_type()) << LogValue("appid", msg.app_id());
}