#include "LoginNetLogic.h"
#include <Guid.h>
#include "ProtoMessage.h"
#include "LoginApp.h"
#include "ClientManager.h"

LoginNetLogic::LoginNetLogic()
{
}

LoginNetLogic::~LoginNetLogic()
{
}

void LoginNetLogic::OnMessage(const NetPacket& packet)
{
	NetMessage* nmsg = (NetMessage*)(packet.mBody);

	auto msgType = theProtoMsgMgr->GetMsgType(nmsg);
#ifdef DEBUG
	LOG(INFO) << "msg " << msgType;
#endif
	switch (msgType)
	{
	case Msg_VerifyAccountReq:
		OnRegisterClient(nmsg, packet.mFD);
		break;
	case Msg_VerifyAccountRes:
		OnUnRegisterClient(nmsg);
		break;
	default:
		NetInterface::OnMessage(packet, msgType);
		break;
	}
}

void LoginNetLogic::OnRegisterClient(const NetMessage* nmsg, int fd)
{
	MsgVerifyAccountReq msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	//验证版本
	msg.version();
// 	auto it = theClientMgr->GetClientByAccount(msg.account());
// 	if (it)//已有验证连接,完成验证前不在做处理
// 		return;
// 	//根据服务器类型生成一个临时Key,便于处理成功后返回LoginApp
// 	int verifyKey = 0;
// 	do 
// 	{
// 		verifyKey = theGuid->Generate32Guid(ESAT_Login);
// 		it = theClientMgr->AddObject(verifyKey);
// 	} while (it == NULL);

	auto it = theClientMgr->AddObject(msg.account());
	if (it)//已有验证连接,完成验证前不在做处理
		return;
	it->SetFD(fd);//网络中间层绑定
//	it->SetClientID(verifyKey);
	it->SetAccount(msg.account());
	AttachSession(it);//网络底层连接绑定
	SMsgVerifyAccountReq bcMsg;
	bcMsg.mutable_base()->set_type(Msg_VerifyAccountReq);
	bcMsg.set_account(msg.account());
	bcMsg.set_password(msg.password());
	bcMsg.set_dev_type(msg.dev_type());
	bcMsg.set_dev_key(msg.dev_key());
	bcMsg.set_pf_type(msg.pf_type());
	bcMsg.set_verify_key(0);//关于验证Key最简单的生成规则用一个时间戳移位后 + 某个随机值,即可,不用担心重复,每个人都不一样.即使重复也无所谓
	theLoginApp->GetBCSession()->SendToBC(&bcMsg);
}

void LoginNetLogic::OnUnRegisterClient(const NetMessage* nmsg)
{
	SMsgVerifyAccountRes msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto it = theClientMgr->GetObject(msg.account());
	if (!it)
		return;
	MsgVerifyAccountRes cMsg;
	cMsg.mutable_base()->set_type(Msg_VerifyAccountRes);
	cMsg.set_base_ip(msg.base_ip());
	cMsg.set_base_port(msg.base_port());
	cMsg.set_base_key(msg.base_key());
	it->SendToClient(&cMsg);
	//考虑加入一个删除队列,做延迟删除
// 	OnDisconnect(it->GetIndex());
// 	theClientMgr->RemoveObject(it->GetAccount());
}