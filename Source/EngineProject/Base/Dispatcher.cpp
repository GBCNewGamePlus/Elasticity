#include "Dispatcher.h"

Dispatcher* Dispatcher::instance = 0;

Dispatcher::Dispatcher() {}

Dispatcher* Dispatcher::GetInstance()
{
	if (!instance)
		instance = new Dispatcher();
	return instance;
}

void Dispatcher::Subscribe(const EventType descriptor, void(*slot)(const Event& e))
{

	observers[descriptor].push_back(slot);
}

void Dispatcher::Post(const Event& event)
{
	EventType type = event.descriptor;
	if (observers.find(type) == observers.end())
		return;
	auto&& listOfFunctions = observers.at(type);
	for (auto&& theFunction : listOfFunctions)
		theFunction(event);
}