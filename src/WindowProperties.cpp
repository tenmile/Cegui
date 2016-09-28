#include "WindowProperties.h"
#include "Window.h"
#include "Font.h"
#include "PropertyHelper.h"
#include "Exceptions.h"
#include "WindowFactoryManager.h"
#include <cstdlib>
#include <cstdio>

namespace CEGUI
{

namespace WindowProperties
{

String ID::get(const Property *receiver) const
{
	return PropertyHelper::uintToString(static_cast<const Window*>(receiver)->getID());
}
void ID::set(PropertyReceiver *receiver, const String &value)
{
	static_cast<Window*>(receiver)->setID(PropertyHelper::stringToUint(value));
}

}

}