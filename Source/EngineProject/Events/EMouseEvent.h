#ifndef __EMOUSE_EVENT_H__
#define __EMOUSE_EVENT_H__

#include "../Base/Event.h"

class EMouseEvent : public Event
{
public:
	int x;
	int y;
	bool leftClick;
	EMouseEvent(int _x, int _y, bool _leftClick);
	~EMouseEvent();
};

#endif