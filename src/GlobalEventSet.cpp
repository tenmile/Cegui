#include "GlobalEventSet.h"
#include "Logger.h"

namespace CEGUI
{

template<> GlobalEventSet* Singleton<GlobalEventSet>::ms_Singleton=0;

GlobalEventSet::GlobalEventSet()
{
	char addr_buff[32];
	sprintf(addr_buff, "%p", static_cast<void *>(this));
	Logger::getSingleton().logEvent("CEGUI::GlobalEventSet singleton created."+String(addr_buff));
}
GlobalEventSet::~GlobalEventSet()
{
	char addr_buff[32];
	sprintf(addr_buff, "%p", static_cast<void *>(this));
	Logger::getSingleton().logEvent("CEGUI::GlobalEventSet singleton destroyed."+String(addr_buff));
}
GlobalEventSet& GlobalEventSet::getSingleton()
{
	return Singleton<GlobalEventSet>::getSingleton();
}
GlobalEventSet* GlobalEventSet::getSingletonPtr()
{
	return Singleton<GlobalEventSet>::getSingletonPtr();
}
void GlobalEventSet::fireEvent(const String &name, EventArgs &args, const String &eventNamespace)
{
	fireEvent_impl(eventNamespace+"/"+name, args);
}

}