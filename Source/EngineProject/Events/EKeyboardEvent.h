#ifndef __EKEYBOARD_EVENT_H__
#define __EKEYBOARD_EVENT_H__

#include "../Base/Event.h"

class EKeyboardEvent : public Event
{
public:
	int keyInt;
	char keyChar;
	bool isChar;
	EKeyboardEvent(int _keyInt);
	EKeyboardEvent(char _keyChar);
	~EKeyboardEvent();
};

#endif
