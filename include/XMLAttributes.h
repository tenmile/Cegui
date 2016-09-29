#pragma once

#include "Base.h"
#include "String.h"
#include <map>

namespace CEGUI
{

class CEGUIEXPORT XMLAttributes
{
public:
	XMLAttributes();
	virtual ~XMLAttributes();

	void add(const String &attrName, const String &attrValue);
	void remove(const String &attrValue);
	bool exists(const String &attrValue) const;
	size_t getCount() const;
	const String& getName(size_t index) const;
	const String& getValue(size_t index) const;
	const String& getValue(const String &attrName) const;
	const String& getValueAsString(const String &attrName, const String &def="") const;
	bool getValueAsBool(const String &attrName, bool def=false) const;
	int getValueAsInteger(const String &attrName, int def=0) const;
	float getValueAsFloat(const String &attrName, float def = 0.0f) const;
protected:
	typedef std::map<String, String, String::FastLessCompare> AttributeMap;
	AttributeMap d_attrs;
};

}