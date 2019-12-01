#ifndef __EVENT_H__
#define __EVENT_H__

enum EventType
{
	MouseEvent,
	KeyboardEvent
};

class Event
{
public:
	EventType descriptor;
};

#endif