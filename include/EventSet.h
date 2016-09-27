#pragma once

#include "Base.h"
#include "String.h"
#include "Event.h"
#include "IteratorBase.h"
#include <map>

namespace CEGUI
{

class CEGUIEXPORT EventSet
{
public:
	EventSet();
	virtual ~EventSet();

	void addEvent(const String &name);
	void removeEvent(const String &name);
	void removeAllEvents(void);
	bool isEventPresent(const String &name);
	virtual Event::Connection subscribe(const String &name, Event::Subscriber subscriber);
	virtual Event::Connection subscribe(const String &name, Event::Group group, Event::Subscriber subscriber);
	virtual Event::Connection subscribeScriptedEvent(const String &name, const String &subscriber_name);
	virtual void fireEvent(const String &name, EventArgs &args, const String &eventNamespace="");
	
	bool isMuted(void) const;
	void setMutedState(bool setting);
protected:
	Event *getEventObject(const String &name, bool autoAdd=false);
	void fireEvent_impl(const String &name, EventArgs &args);

	EventSet(EventSet&){}
	EventSet& operator=(EventSet&){return *this;}

	typedef std::map<String, Event*, String::FastLessCompare> EventMap;
	EventMap d_events; //�¼�������
	bool d_muted;      //�Ƿ����δ��¼������¼�
public:
	typedef ConstBaseIterator<EventMap> Iterator;
	Iterator getIterator(void) const;
};

}