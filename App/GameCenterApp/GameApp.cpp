#include "GameApp.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

bool GameApp::SentToGame(::google::protobuf::Message* pbMsg)
{
	return theGameCenterApp->GetNetLogic()->OnSend(this, pbMsg);
}

void GameApp::Connected()
{

}

void GameApp::Disconnected()
{

}

void GameApp::OnMsg(const NetMessage* nmsg, int msgType /* = 0 */)
{

}
