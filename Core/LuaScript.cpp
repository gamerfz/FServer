#include "LuaScript.h"

LuaScript::LuaScript() :
mLuaState(NULL)
{
}

LuaScript::~LuaScript()
{
}

bool LuaScript::Init(std::string file)
{
	mLuaState = luaL_newstate();
	luaL_openlibs(mLuaState);

	if (!Regisger())
	{
		lua_close(mLuaState);
		mLuaState = NULL;
		return false;
	}
	lua_pcall(mLuaState, 0, 0, 0);

	if (luaL_loadfile(mLuaState, file.c_str()) != 0)
		return false;

	if (lua_pcall(mLuaState, 0, 0, 0) != 0)//出错话说明脚本有问题
		return false;
	return true;
}

bool LuaScript::Regisger()
{
// 	//luabridge::getGlobalNamespace(mLuaState).addCFunction()
// 	//luabridge::getGlobalNamespace(mLuaState).beginClass().endClass();
// 	luabridge::getGlobalNamespace(mLuaState)
// 		.beginClass<LuaScript>("LuaScript")
// 		.addFunction("func1", &LuaScript::func1)
// 		.endClass();
// 

	return true;
}

luabridge::LuaRef LuaScript::RunScript(std::string fun)
{
	auto func = luabridge::getGlobal(mLuaState, fun.c_str());
	return func;
}