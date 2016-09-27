#pragma once

#include "EventSet.h"
#include "Singleton.h"

namespace CEGUI
{

class CEGUIEXPORT GlobalEventSet: public EventSet, public Singleton<GlobalEventSet>
{
public:
	GlobalEventSet();
	~GlobalEventSet();

	static GlobalEventSet& getSingleton();
	static GlobalEventSet* getSingletonPtr();

	virtual void fireEvent(const String &name, EventArgs &args, const String &eventNamespace="");
};

}