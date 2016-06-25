#include "App.h"
#include <Guid.h>
#include "BaseAppManager.h"
#include "BCPlayerManager.h"

App::App()
{
}

App::~App()
{
}

bool App::SendToApp(::google::protobuf::Message* pbMsg)
{
	return theBaseCenterApp->GetNetLogic()->OnSend(this, pbMsg);
}

void App::Connected()
{
	LOG(INFO) << "App connected!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID());
}

void App::Disconnected()
{
	LOG(INFO) << "App disconnected!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID());
}

void App::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (GetAppType())
	{
	case ESAT_GameCenter:
		OnGCMsg(nmsg, msgType);
		break;
	case ESAT_Base:
		OnBaseMsg(nmsg, msgType);
		break;
	case ESAT_Login:
		OnLoginMsg(nmsg, msgType);
		break;
	default:
		LOG(ERROR) << "Unknown App msg!" << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID()) << LogValue("msgtype", msgType);
		break;
	}
}

void App::OnGCMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (msgType)
	{
		/*		MESSAGE_HANDLE(Msg_RespondApp, MsgRespondApp, OnMsgRespondApp)
		/*		MESSAGE_HANDLE(Msg_RespondApp+1, MsgRespondApp, OnMsgRespondApp)*/
	default:
		LOG(INFO) << "Unknown msg!" << LogValue("msgType", msgType);
		break;
	};
}
void App::OnBaseMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
void App::OnLoginMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
	switch (msgType)
	{
		MESSAGE_HANDLE(Msg_VerifyAccountReq, SMsgVerifyAccountReq, OnSMsgVerifyAccountReq)
	default:
		LOG(INFO) << "Unknown msg!" << LogValue("msgType", msgType);
		break;
	};
}

void App::OnSMsgVerifyAccountReq(SMsgVerifyAccountReq* msg)
{
	SMsgVerifyAccountRes res;
	res.mutable_base()->set_type(Msg_VerifyAccountRes);
	res.mutable_base()->set_result(EVAR_Success);
	//帐号验证,包括内存和数据库
	//分配base服务器地址,并通知base
// 	auto it = theBCPlayerMgr->GetObject(res.)

	auto verifyKey = theGuid->Generate32Guid(ESAT_BaseCenter);
	auto baseapp = theBaseAppMgr->DispatchBaseApp();
	if (baseapp)
	{
		auto bCfg = theConfigMgr->GetServerCfg(baseapp->GetAppID());
		if (bCfg)
		{
			res.set_base_ip(bCfg->serverIP);
			res.set_base_port(bCfg->serverPort);
			//res.set_base_ip(bCfg->serverIP);
		}
		else
			res.mutable_base()->set_result(EVAR_Fail);
	}
	else
		res.mutable_base()->set_result(EVAR_Fail);
}