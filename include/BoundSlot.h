#pragma once

#include "Base.h"
#include "SubsrcibeSlot.h"

namespace CEGUI
{

class CEGUIEXPORT BoundSlot
{
public:
	typedef unsigned int Group;

	BoundSlot(Group group, const SubscriberSlot &subscriber, Event &event);
	BoundSlot(const BoundSlot &other);
	~BoundSlot();

	bool connected() const;
	void disconnect();
	bool operator==(const BoundSlot &other) const;
	bool operator!=(const BoundSlot &other) const;
private:
	friend class Event;
	//½ûÓÃ=²Ù×÷
	BoundSlot& operator=(const BoundSlot &other);
	Group d_group;
	SubscriberSlot *d_subscriber;
	Event *d_event;
};

}