#include "XMLAttributes.h"
#include "Exceptions.h"
#include <sstream>
#include <iterator>

namespace CEGUI
{

XMLAttributes::XMLAttributes() {}
XMLAttributes::~XMLAttributes() {}

void XMLAttributes::add(const String &attrName, const String &attrValue)
{
	d_attrs[attrName] = attrValue;
}

void XMLAttributes::remove(const String &attrName)
{
	AttributeMap::iterator pos = d_attrs.find(attrName);
	if (pos != d_attrs.end())
	{
		d_attrs.erase(pos);
	}
}

bool XMLAttributes::exists(const String &attrName) const
{
	return d_attrs.find(attrName) != d_attrs.end();
}

size_t XMLAttributes::getCount() const
{
	return d_attrs.size();
}

const String& XMLAttributes::getName(size_t index) const
{
	if (index>=d_attrs.size())
	{
		CEGUI_THROW(InvalidRequestException("XMLAttributes::getName - The specified index is out of range for this XMLAttributes block."));
	}
	AttributeMap::const_iterator iter = d_attrs.begin();
	std::advance(iter, index);
	return (*iter).first;
}

const String& XMLAttributes::getVaule(size_t index) const
{
	if (index>=d_attrs.size())
	{
		CEGUI_THROW(InvalidRequestException("XMLAttributes::getName - The specified index is out of range for this XMLAttributes block."));
	}
	AttributeMap::const_iterator iter = d_attrs.begin();
	std::advance(iter, index);
	return (*iter).second;
}



}