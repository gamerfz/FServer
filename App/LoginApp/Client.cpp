#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}

void Client::OnReset()
{
	SetFD(-1);
	SetIndex(-1);
	mClientID = 0;
	mAccount = "";
}


bool Client::SendToClient(::google::protobuf::Message* pbMsg)
{
	return theLoginApp->GetNetLogic()->OnSend(this, pbMsg);
}

void Client::Connected()
{

}

void Client::Disconnected()
{

}

void Client::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
