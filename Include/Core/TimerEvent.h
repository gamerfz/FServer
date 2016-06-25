/***********************************************************************
*FileName	:  TimerEvent
*Author		:  fz
*Date		:  2016.1.17
*Description:  定时器事件
************************************************************************/
#pragma once
#include <event2/event.h>
#include <event2/event_struct.h>
#include <memory>

class TimerEvent
{
public:
	TimerEvent(event_base* evBase, int milliSecs, bool repeated);
	virtual~TimerEvent();
	virtual void OnTimer() = 0;

	event m_event;
	timeval m_timeval;
// private:
// 	friend bool AddTimer(TimerEvent* te);
// 	friend void RemoveTimer(TimerEvent* te);
// 	friend bool ResetTimer(TimerEvent* te, int milliSecs);
};

//除了使用以下模版,也可以直接继承TimerEvent,重写OnTimer函数
bool AddTimer(TimerEvent* te);
void RemoveTimer(TimerEvent* te);
bool ResetTimer(TimerEvent* te, int milliSecs = 0);
//std::shared_ptr版本
bool AddTimer(std::shared_ptr<TimerEvent> te);
void RemoveTimer(std::shared_ptr<TimerEvent> te);
bool ResetTimer(std::shared_ptr<TimerEvent> te, int milliSecs = 0);

//C:类 Fn:类的函数 R:函数返回类型
template<class C, class R>
class Timer : public TimerEvent
{
	typedef R(C::*Fn)();
	C* m_class;
	Fn m_fn;
public:
	Timer(C* pClass, Fn fn, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn){}
	virtual void OnTimer(){ (m_class->*m_fn)(); }
};

//C:类 Fn:类的函数 R:函数返回类型 P1:函数参数1
template<class C, class R, class P1>
class Timer1 : public TimerEvent
{
	typedef R(C::*Fn)(P1 p1);
	C* m_class;
	Fn m_fn;
	P1 m_p1;
public:
	Timer1(C* pClass, Fn fn, P1 p1, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn), m_p1(p1){}
	virtual void OnTimer(){ (m_class->*m_fn)(m_p1); }
};

//C:类 Fn:类的函数 R:函数返回类型 P1:函数参数1 P2:函数参数2
template<class C, class R, class P1, class P2>
class Timer2 : public TimerEvent
{
	typedef R(C::*Fn)(P1 p1, P2 p2);
	C* m_class;
	Fn m_fn;
	P1 m_p1;
	P2 m_p2;
public:
	Timer2(C* pClass, Fn fn, P1 p1, P2 p2, event_base* evBase, int milliSecs, bool repeated = false) :
		TimerEvent(evBase, milliSecs, repeated), m_class(pClass), m_fn(fn), m_p1(p1), m_p2(p2){}
	virtual void OnTimer(){ (m_class->*m_fn)(m_p1, m_p2); }
};
