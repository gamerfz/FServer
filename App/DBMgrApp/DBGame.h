#pragma once
#include <DBInterface.h>

class DBGame : public DBInterface
{
	int mDBID;
public:
	DBGame();
	~DBGame();

	void SetDBID(int id) { mDBID = id; }
};



/*
#define theDBGame DBGame::GetInstance()
class DBGame : public DBInterface, public Singleton<DBGame>
{

};

InitSingleton(DBGame)*/