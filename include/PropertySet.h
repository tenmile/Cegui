#pragma once

#include "Base.h"
#include "String.h"
#include "IteratorBase.h"
#include "Property.h"
#include <map>

namespace CEGUI
{

class CEGUIEXPORT PropertySet: public PropertyReceiver
{
public:
	PropertySet(){}
	virtual ~PropertySet(){}
	void addProperty(Property *property);
	void removeProperty(const String &name);
	void clearProperties();
	bool isPropertyPresent(const String &name) const;
	const String& getPropertyHelp(const String &name) const;
	const String& getProperty(const String &name) const;
	void setProperty(const String &name, const String &value);
	bool isPropertyDefault(const String &name) const;
	String getPropertyDefault(const String &name) const;
private:
	typedef std::map<String, Property*, String::FastLessCompare> PropertyRegistry;
	PropertyRegistry d_properties;
public:
	typedef ConstBaseIterator<PropertyRegistry> Iterator;
	Iterator getIterator() const;

};

}