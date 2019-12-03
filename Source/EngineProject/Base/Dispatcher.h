#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class Dispatcher
{
public:
	using SlotType = std::function< void(const Event&) >;
	void Subscribe(const EventType descriptor, SlotType&& slot);

	void Subscribe(const EventType descriptor, void(*slot)(const Event& e) );

	void Post(const Event& event);
	static Dispatcher* GetInstance();
	
private:
	std::map<EventType, std::vector<SlotType>> observers;
	std::map<EventType, std::vector<void(*)(const Event&)>> observers2;
	static Dispatcher* instance;
	Dispatcher();
};

#endif
