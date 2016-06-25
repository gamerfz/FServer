#pragma once
#include "LoginApp.h"//注意顺序,必须在WinDump.h前
#ifdef WIN32
#include "WinDump.h"
#endif

#include <vector>
void fun1(int p1, int p2)
{
	&p1;//-		&p1	0x000000bc7cf7fa10 {3}	int *
	&p2;//-		&p2	0x000000bc7cf7fa18 {5}	int *
	p2;//5
	int i = 0;
	i++;
}
char* fun2()
{
	char a[] = "hesad111111111111123";
	return a;
}
class AA
{
	bool ma;
public:
	AA(){};
	~AA(){};

	bool ba(){ return ma; }
};

class BB
{
	bool mb;
public:
	BB(){};
	~BB(){};

	bool bb(){ return mb; }
};

class CC : public BB, public AA
{
public:
	CC(){};
	~CC(){};
};

int main(int argc, char* argv[])
{
#ifdef WIN32
	WinDump wDump("LoginApp");
#endif
	if (!theConfigMgr->ParseCommond(argc, argv))
		return false;
	FLAGS_max_log_size = 100;/*log文件大小MB*/
	FLAGS_stop_logging_if_full_disk = false;/*避免写日志磁盘已满*/ // 暂不避免
	FLAGS_logbufsecs = 0;/*实时输出*/
	FLAGS_colorlogtostderr = true;
	google::InitGoogleLogging("");
	google::SetLogDestination(google::GLOG_ERROR, "../Binary/Log/Error");
	google::SetLogDestination(google::GLOG_INFO, "../Binary/Log/Info");
	google::SetStderrLogging(google::GLOG_INFO);
	std::stringstream ss;
	ss << "LoginApp" << theConfigMgr->GetAppID() << "-";
	google::SetLogFilenameExtension(ss.str().c_str());//设置文件名扩展
	
	LOG(INFO) << "info test";
	LOG(ERROR) << "error test";


	char a = 64;
	int b = 0;
	a <<= 1;//越界,负数
	b = a;
	a >>= 1;
	b = a;

	int c[2] = { 0, 0 };
	int *p = c;
	*p++ = 1;//c[0]=1,*p++ = c[1]

	int oneCnt = 0;
	for (int i = 0; i < 2006; ++i)
	{
		if (i % 10 == 1)
			oneCnt++;
		if (i / 10 % 10 == 1)
			oneCnt++;
		if (i / 100 % 10 == 1)
			oneCnt++;
		if (i / 1000 % 10 == 1)
			oneCnt++;
	}

	int d = 3, e = 4, f = 5;
	int g = d++ > --e&&f--&&++f;// d先运行后++ ,f-- ++f无意义,都是true

	int j = 3;
	int k = 5;
	&k;
	&j;
	fun1(j, k);

	//其实很好理解,看继承的先后顺序,先继承的类占用地址靠前,后继承的类靠后,
	//而new的地址是重基类开始算的,所以子类初始地址应该和首个继承的基类地址相同,之后是后续的基类地址
	CC* cc = new CC;
	AA* ca = (AA*)cc;
	BB* cb = (BB*)cc;

	//带了反斜杠n,可以正常拷贝输出?
	char* p1 = (char*)malloc(8);
	char p2[5];
	char* str = "Hi world";
	strcpy(p1, str);
	strcpy(p2, str);

	char* p3 = fun2();
	char* str1 = "hello world";
	strcpy(p3, str1);

	std::vector<int> veci;
	for (int i = 0; i < 10; i++)
		veci.push_back(i);

	bool del = true;
	for (auto it = veci.begin(); it != veci.end();)
	{
		it = veci.erase(it);
	}


	if (theLoginApp->Init())
		theLoginApp->StartUp();
	theLoginApp->ShutDown();

	return 0;
}