#include "WRFactoryRegisterer.h"
#include "WindowFactoryManager.h"

namespace CEGUI
{

WRFactoryRegisterer::WRFactoryRegisterer(const CEGUI::utf8 *type):
	d_type(type) {}
WRFactoryRegisterer::~WRFactoryRegisterer() {}
void WRFactoryRegisterer::registerFactory()
{
	if (CEGUI::WindowFactoryManager::getSingleton().isFactoryPresent(d_type))
	{
		CEGUI::Logger::getSingleton().logEvent("Factory for '" +CEGUI::String(d_type)+ "' appears to be already registered, skipping.", CEGUI::Informative);
	} 
	else
	{
		this->doFactoryAdd();
	}
}
void WRFactoryRegisterer::unregisterFactory()
{
	WindowFactoryManager::getSingleton().removeFactory(d_type);
}

}