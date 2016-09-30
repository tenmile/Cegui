#include "WindowRendererModule.h"
#include "WRFactoryRegisterer.h"
#include "Exceptions.h"

namespace CEGUI
{

WindowRendererModule::~WindowRendererModule() {}
void WindowRendererModule::registerFactory(const String &type_name)
{
	FactoryRegisterer::iterator i = d_registery.begin();
	for (; i != d_registery.end(); ++i)
	{
		if ((*i)->d_type == type_name)
		{
			(*i)->registerFactory();
			return;
		}
	}
	CEGUI_THROW(UnknownObjectException("No factory for WindowRenderer type '" +type_name+ "' in this module."));
}
uint WindowRendererModule::registerAllFactories()
{
	FactoryRegisterer::iterator i = d_registery.begin();
	for (; i != d_registery.end(); ++i)
	{
		(*i)->registerFactory();
	}
	return static_cast<uint>(d_registery.size());
}

void WindowRendererModule::unregisterFactory(const String &type_name)
{
	FactoryRegisterer::iterator i = d_registery.begin();
	for (; i!=d_registery.end(); ++i)
	{
		if ((*i)->d_type == type_name)
		{
			(*i)->unregisterFactory();
			return;
		}
	}
}

uint WindowRendererModule::unregisterAllFactories()
{
	FactoryRegisterer::iterator i = d_registery.begin();
	for (; i!=d_registery.end(); ++i)
	{
		(*i)->unregisterFactory();
	}
	return static_cast<uint>(d_registery.size());
}


}