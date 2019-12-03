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

void Dispatcher::Subscribe(const EventType descriptor, void(*slot)(const Event& e))
{

	observers2[descriptor].push_back(slot);
}
void Dispatcher::Post(const Event& event)
{
	EventType type = event.descriptor;

	// Ignore events for which we do not have an observer (yet).
	if (observers2.find(type) == observers2.end())
		return;

	auto&& listOfFunctions = observers2.at(type);

	for (auto&& theFunction : listOfFunctions)
		theFunction(event);
}