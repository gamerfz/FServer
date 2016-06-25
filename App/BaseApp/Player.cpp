#include "Player.h"
#include "BaseApp.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::SendToClient(::google::protobuf::Message* pbMsg)
{
	return theBaseApp->GetNetLogic()->OnSend(this, pbMsg);
}

bool Player::SendToBC(::google::protobuf::Message* pbMsg)
{
	return theBaseApp->GetBCSession()->SendToBC(pbMsg);
}

bool Player::SendToGame(::google::protobuf::Message* pbMsg)
{
	return theBaseApp->GetGameSession()->SendToGame(pbMsg);
}

void Player::Connected()
{
	LOG(INFO) << "Player connected!";
}

void Player::Disconnected()
{
	LOG(INFO) << "Player disconnected!"/* << LogValue("apptype", GetAppType()) << LogValue("appid", GetAppID())*/;
}

void Player::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{
}
