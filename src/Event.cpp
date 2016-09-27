#include "Event.h"
#include "EventArgs.h"

#include <algorithm>

namespace CEGUI
{

class SubComp
{
public:
	SubComp(const BoundSlot &s):
	  d_s(s){}
	bool operator()(std::pair<Event::Group, Event::Connection> e) const
	{
		return *(e.second) == d_s;
	}
private:
	void operator=(const SubComp&){}
	const BoundSlot &d_s;
};

Event::~Event()
{
	SlotContainer::iterator iter(d_slots.begin());
	const SlotContainer::const_iterator end_iter(d_slots.end());

	for (; iter!=end_iter; ++iter)
	{
		iter->second->d_event = 0;
		iter->second->d_subscriber->cleanup();
	}

	d_slots.clear();
}

Event::Connection Event::subscriber(const Event::Subscriber &slot)
{
	return subscriber(static_cast<Group>(-1), slot);
}

Event::Connection Event::subscriber(Event::Group group, const Event::Subscriber &slot)
{
	Event::Connection c(new BoundSlot(group, slot, *this));
	d_slots.insert(std::pair<Group, Connection>(group, c));
	return c;
}

void Event::operator()(EventArgs &args)
{
	SlotContainer::iterator iter(d_slots.begin());
	const SlotContainer::const_iterator end_iter(d_slots.end());

	for (; iter!=end_iter; ++iter)
	{
		if ((*iter->second->d_subscriber)(args))
		{
			++args.handled;
		}
	}
}

void Event::unsubscribe(const BoundSlot &slot)
{
	SlotContainer::iterator curr = std::find_if(d_slots.begin(), d_slots.end(), SubComp(slot));
	if (curr != d_slots.end())
	{
		d_slots.erase(curr);
	}
}

}
