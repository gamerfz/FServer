#include "TimerEvent.h"

static void TimerCallback(evutil_socket_t fd, short event, void *arg)
{
	auto timer = (TimerEvent*)arg;
	timer->OnTimer();
}

TimerEvent::TimerEvent(event_base* evBase, int milliSecs, bool repeated)
{
	short flag = 0;
	if (repeated)
		flag |= EV_PERSIST;
	m_timeval.tv_sec = milliSecs / 1000;
	m_timeval.tv_usec = (milliSecs % 1000) * 1000;
	event_assign(&m_event, evBase, -1, flag, TimerCallback, (void*)this);
}

TimerEvent::~TimerEvent()
{
	event_del(&this->m_event);
}

bool AddTimer(TimerEvent* te)
{
	if (!te)
		return false;

	return event_add(&te->m_event, &te->m_timeval) == 0;
}

void RemoveTimer(TimerEvent* te)
{
	event_del(&te->m_event);
}

bool ResetTimer(TimerEvent* te, int milliSecs /* = 0 */)
{
	RemoveTimer(te);
	if (milliSecs > 0)
	{
		te->m_timeval.tv_sec = milliSecs / 1000;
		te->m_timeval.tv_usec = (milliSecs % 1000) * 1000;
	}
	return AddTimer(te);
}

bool AddTimer(std::shared_ptr<TimerEvent> te)
{
	if (!te)
		return false;
	return event_add(&te->m_event, &te->m_timeval) == 0;
}

void RemoveTimer(std::shared_ptr<TimerEvent> te)
{
	event_del(&te->m_event);
}

bool ResetTimer(std::shared_ptr<TimerEvent> te, int milliSecs /* = 0 */)
{
	RemoveTimer(te);
	if (milliSecs > 0)
	{
		te->m_timeval.tv_sec = milliSecs / 1000;
		te->m_timeval.tv_usec = (milliSecs % 1000) * 1000;
	}
	return AddTimer(te);
}