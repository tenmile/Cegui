#include "BoundSlot.h"
#include "Event.h"

namespace CEGUI
{

BoundSlot::BoundSlot(Group group, const SubscriberSlot &subscriber, Event &event):
	d_group(group),
	d_subscriber(new SubscriberSlot(subscriber)),
	d_event(&event){}
BoundSlot::BoundSlot(const BoundSlot &other):
	d_group(other.d_group),
	d_subscriber(other.d_subscriber),
	d_event(other.d_event){}
BoundSlot::~BoundSlot()
{
	disconnect();
	delete d_subscriber;
}

BoundSlot& BoundSlot::operator=(const BoundSlot &other)
{
	d_group		 = other.d_group;
	d_subscriber = other.d_subscriber;
	d_event		 = other.d_event;

	return *this;
}
bool BoundSlot::operator==(const BoundSlot &other) const
{
	return d_subscriber == other.d_subscriber;
}
bool BoundSlot::operator!=(const BoundSlot &other) const
{
	return !(*this == other);
}
//连接的含义在于是否绑定了函数
bool BoundSlot::connected() const
{
	return (d_subscriber!=0) && d_subscriber->connected();
}
void BoundSlot::disconnect()
{
	if (connected())
	{
		d_subscriber->cleanup();
	}
	if (d_event)
	{
		d_event->unsubscribe(*this);
		d_event = 0;
	}
}


}