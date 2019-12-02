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
	void subscribe(const EventType descriptor, SlotType&& slot);
	void post(const Event& event);

private:
	std::map<EventType, std::vector<SlotType>> _observers;
};

#endif
