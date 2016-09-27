#include "EventSet.h"
#include "Exceptions.h"
#include "GlobalEventSet.h"
#include "ScriptModule.h"
#include "System.h"

namespace CEGUI
{

EventSet::EventSet():
	d_muted(false){}
EventSet::~EventSet()
{
	removeAllEvents();
}

void EventSet::addEvent(const String &name)
{
	if (isEventPresent(name))
	{
		CEGUI_THROW(AlreadyExistsException("An event named '"+name+"' already exists in the EventSet."));
	}
	d_events[name] = new Event(name);
}
void EventSet::removeEvent(const String &name)
{
	EventSet::Iterator pos = d_events.find(name);
	if (pos != d_events.end())
	{
		delete pos->second;
		d_events.erase(pos);
	}
}
void EventSet::removeAllEvents()
{
	EventMap::iterator pos = d_events.begin();
	EventMap::iterator end = d_events.end();
	for (; pos != end; ++pos)
	{
		delete pos->second;
	}
	d_events.clear();
}
bool EventSet::isEventPresent(const String &name)
{
	return (d_events.find(name) != d_events.end());
}
Event::Connection EventSet::subscribeScriptedEvent(const String &name, const String &subscriber_name)
{
	ScriptModule *sm = System::getSingletonPtr();
	if (!sm)
	{
		CEGUI_THROW(InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available"));
	}
	return sm->subscribeEvent(this, name, subscriber_name);
}
Event::Connection EventSet::subscribeScriptedEvent(const String &name, Event::Group group, String &subscriber_name)
{
	ScriptModule *sm = System::getSingletonPtr();
	if (!sm)
	{
		CEGUI_THROW(InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available"));
	}
	return sm->subscribeEvent(this, name, group, subscriber_name);
}
Event::Connection EventSet::subscribeEvent(const String &name, Event::Subscriber subscriber)
{
	return getEventObject(name, true)->subscribe(subscriber);
}
Event::Connection EventSet::subscribeEvent(const String &name, Event::Group group, Event::Subscriber subscriber)
{
	return getEventObject(name, true)->subscribe(subscriber, group);
}
void EventSet::fireEvent(const String &name, EventArgs &args, const String &eventNamespace)
{
	GlobalEventSet::getSingleton().fireEvent(name, args, eventNamespace);
	fireEvent_impl(name, args);
}
bool EventSet::isMuted() const
{
	return d_muted;
}
void EventSet::setMutedState(bool setting)
{
	d_muted = setting;
}
Event* EventSet::getEventObject(const String &name, bool autoAdd)
{
	EventMap::iterator pos = d_events.find(name);

	if (pos==d_events.end())
	{
		if (autoAdd)
		{
			addEvent(name);
			return d_events.find(name)->second;
		} 
		else
		{
			return 0;   //不抛出异常
		}
	}
	return pos->second;
}
void EventSet::fireEvent_impl(const String &name, EventArgs &args)
{
	Event *ev = getEventObject(name);
	if ((ev!=0) && !d_muted)  //d_muted在这里起作用，如果为true，则事件响应函数不会被执行
	{
		(*ev)(args);
	}
}
EventSet::Iterator EventSet::getIterator() const
{
	return Iterator(d_events.begin(), d_events.end());
}

}