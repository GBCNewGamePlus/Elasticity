#include "EKeyboardEvent.h"

EKeyboardEvent::EKeyboardEvent(int _keyInt)
{
	descriptor = EventType::KeyboardEvent;
	keyInt = _keyInt;
	isChar = false;
}

EKeyboardEvent::EKeyboardEvent(char _keyChar)
{
	descriptor = EventType::KeyboardEvent;
	keyChar = _keyChar;
	isChar = true;
}

EKeyboardEvent::~EKeyboardEvent()
{
}