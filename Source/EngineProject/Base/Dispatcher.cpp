#include "Dispatcher.h"

Dispatcher* Dispatcher::instance=0;

Dispatcher::Dispatcher() {}

Dispatcher* Dispatcher::GetInstance()
{
	if (!instance)
		instance = new Dispatcher();
	return instance;
}

void Dispatcher::Subscribe(const EventType descriptor, SlotType&& slot)
{
	observers[descriptor].push_back(slot);
}

void Dispatcher::Post(const Event& event)
{
	EventType type = event.descriptor;

	// Ignore events for which we do not have an observer (yet).
	if (observers.find(type) == observers.end())
		return;

	auto&& listOfFunctions = observers.at(type);

	for (auto&& theFunction : listOfFunctions)
		theFunction(event);
}