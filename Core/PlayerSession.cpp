#include "PlayerSession.h"

PlayerSession::PlayerSession()
{
}

PlayerSession::~PlayerSession()
{
}

void PlayerSession::OnReset()
{
	SetFD(-1);
	SetIndex(-1);
}

void PlayerSession::Connected()
{

}

void PlayerSession::Disconnected()
{

}

void PlayerSession::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
