#include "MouseEvent.h"

EMouseEvent::EMouseEvent(int _x, int _y, bool _leftClick)
{
	descriptor = EventType::MouseEvent;
	x = _x;
	y = _y;
	leftClick = _leftClick;
}

EMouseEvent::~EMouseEvent()
{
}
