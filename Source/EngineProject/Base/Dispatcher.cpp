#include "Dispatcher.h"

void Dispatcher::subscribe(const EventType descriptor, SlotType&& slot)
{
	_observers[descriptor].push_back(slot);
}

void Dispatcher::post(const Event& event)
{
	auto type = event.descriptor;

	// Ignore events for which we do not have an observer (yet).
	if (_observers.find(type) == _observers.end())
		return;

	auto&& observers = _observers.at(type);

	for (auto&& observer : observers)
		observer(event);
}