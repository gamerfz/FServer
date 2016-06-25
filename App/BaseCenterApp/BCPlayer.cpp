#include "BCPlayer.h"
#include "ServerDefine.h"

BCPlayer::BCPlayer()
{
}

BCPlayer::~BCPlayer()
{
}

void BCPlayer::OnReset()
{
	mAppID = ESAI_Unknown;
	mGuid = 0;
}