#include "PropertySet.h"
#include "Property.h"
#include "Exceptions.h"

namespace CEGUI
{

void PropertySet::addProperty(Property *property)
{
	if (!property)
	{
		CEGUI_THROW(NullObjectException("The given Property object pointer is invalid."));
	}
	if (d_properties.find(property->getName()) != d_properties.end())
	{
		CEGUI_THROW(AlreadyExistsException("A Property named '" + property->getName() + "' already exists in the PropertySet."));
	}

	d_properties[property->getName()] = property;
}
void PropertySet::removeProperty(const String &name)
{
	PropertyRegistry::iterator pos = d_properties.find(name);

	if (pos != d_properties.end())
	{
		d_properties.erase(pos);
	}
}
void PropertySet::clearProperties()
{
	d_properties.clear();
}
bool PropertySet::isPropertyPresent(const String &name) const
{
	return (d_properties.find(name) != d_properties.end());
}
const String& PropertySet::getPropertyHelp(const String &name) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);

	if (pos == d_properties.end())
	{
		CEGUI_THROW(UnknownObjectException("There is no Property named'" +name+ "' available in the set."));
	}

	return pos->second->getHelp();
}
String PropertySet::getProperty(const String &name) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);
	if (pos==d_properties.end())
	{
		CEGUI_THROW(UnknownObjectException("There is no Property named'" +name+ "' available in the set."));
	}
	return pos->second->get(this);
}
void PropertySet::setProperty(const String &name, const String &value)
{
	PropertyRegistry::iterator pos = d_properties.find(name);
	if (pos==d_properties.end())
	{
		CEGUI_THROW(UnknownObjectException("There is no Property named'" +name+ "' available in the set."));
	}
	pos->second->set(this, value);
}
PropertySet::Iterator PropertySet::getIterator() const
{
	return Iterator(d_properties.begin(), d_properties.end());
}
bool PropertySet::isPropertyDefault(const String &name) const
{
	PropertyRegistry::const_iterator pos = d_properties.find(name);
	if (pos==d_properties.end())
	{
		CEGUI_THROW(UnknownObjectException("There is no Property named'" +name+ "' available in the set."));
	}
	return pos->second->isDefault(this);
}


}