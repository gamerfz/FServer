#pragma once
#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

class LuaScript
{
	lua_State* mLuaState;
public:
	LuaScript();
	virtual~LuaScript();

	virtual bool Init(std::string file);
	virtual bool Regisger();

 	luabridge::LuaRef RunScript(std::string fun);
// 	std::string GetLuaString(std::string name);
// 	std::string GetLuaString(std::string name);
// 	std::string GetLuaString(std::string name);
// 	std::string GetLuaString(std::string name);
// 	std::string GetLuaString(std::string name);
// 	std::string GetLuaString(std::string name);
};

/*
class LuaScript
{
	lua_State* mLuaState;
public:
	LuaScript();
	~LuaScript();

	void Init();
	bool Regisger();

	void Test();

	static int staticData;
	static int getStaticData() { return staticData; }

	static float staticProperty;
	static float getStaticProperty() { return staticProperty; }
	static void setStaticProperty(float f) { staticProperty = f; }

	static int staticCFunc(lua_State *L) { return 0; }

	std::string dataMember;

	char dataProperty;
	char getProperty() const { return dataProperty; }
	void setProperty(char v) { dataProperty = v; }

	void func1() { printf("func1 In Class A\n"); }
	virtual void virtualFunc() { printf("virtualFunc In Class A\n"); }
	int cfunc(lua_State* L) { printf("cfunc In Class A\n");  return 0; }


	virtual void foo1(int a)
	{
		printf("foo1 base %i \n", a);
	}
};
*/

/*
LuaScript::LuaScript() :
mLuaState(NULL)
{
}

LuaScript::~LuaScript()
{
}

void LuaScript::Init()
{
	mLuaState = luaL_newstate();
	luaL_openlibs(mLuaState);

	if (!Regisger())
	{
		lua_close(mLuaState);
		mLuaState = NULL;
		return;
	}
	lua_pcall(mLuaState, 0, 0, 0);
}

bool LuaScript::Regisger()
{
	//luabridge::getGlobalNamespace(mLuaState).addCFunction()
	//luabridge::getGlobalNamespace(mLuaState).beginClass().endClass();
	luabridge::getGlobalNamespace(mLuaState)
		.beginClass<LuaScript>("LuaScript")
		.addFunction("func1", &LuaScript::func1)
		.endClass();


	return true;
}

void LuaScript::Test()
{
	Init();
	/ *简单的堆栈索要操作
	lua_pushstring(mLuaState, "I am so cool~");
	lua_pushnumber(mLuaState, 20);
	if (lua_isstring(mLuaState, 1)){             //判断是否可以转为string
	LOG(INFO) << lua_tostring(mLuaState, 1);  //转为string并返回
	}
	if (lua_isnumber(mLuaState, 2)){
	LOG(INFO) << lua_tonumber(mLuaState, 2);
	}* /

	if (luaL_loadfile(mLuaState, "luat.lua") != 0)
		return;

	if (lua_pcall(mLuaState, 0, 0, 0) != 0)//出错话说明脚本有问题
		return;

	/ *luat.lua
	str = "I am so cool"
	tbl = {name = "shun", id = 20114442}
	tbl2 = {}
	tbl2[1] = 123
	tbl2[2] = 2

	function adds(a,b)
	return a + b
	end
	* /

	auto func1 = luabridge::getGlobal(mLuaState, "adds");
	auto it = func1(1, 2);
	if (!it.isNumber())
		return;
	int val = it.cast<int>();

	auto lr2 = luabridge::getGlobal(mLuaState, "str");
	if (!lr2.isString())
		return;
	auto s = lr2.cast<std::string>();
	auto lr3 = luabridge::getGlobal(mLuaState, "tbl");
	if (!lr3.isTable())
		return;
	int i = lr3.type();
	auto t1 = lr3["name"].cast<std::string>();
	auto t2 = lr3["id"].cast<int>();

	auto lr4 = luabridge::getGlobal(mLuaState, "tbl2");
	if (!lr4.isTable())
		return;
	auto lrt1 = lr4[1].cast<int>();
	auto lrt2 = lr4[2].cast<int>();

	lua_getglobal(mLuaState, "str");

	lua_close(mLuaState);



}*/

/*
str = "I am so cool"
tbl = {name = "shun", id = 20114442}
tbl2 = {}
tbl2[1] = 123
tbl2[2] = 2

function adds(a,b)
return a + b
end

function addto()
local a = 100;
return a + lObj:func1();
end
*/