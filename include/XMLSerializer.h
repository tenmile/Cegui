#pragma once

#include "Base.h"
#include "String"
#include <vector>

namespace CEGUI
{

class CEGUIEXPORT XMLSerializer
{
public:
	XMLSerializer(OutStream &out, size_t indentSpace = 4);
	virtual ~XMLSerializer();
	XMLSerializer& openTag(const String &name);
	XMLSerializer& closeTag();
	XMLSerializer& attribute(const String &name, const String &value);
	XMLSerializer& text(const String &text);
	unsigned int getTagCount() const;

	operator bool() const
	{
		return false == d_error;
	}
	bool operator!() const
	{
		return false != d_error;
	}
protected:
	bool d_error;
	unsigned int d_tagCount;
	size_t d_depth;
	size_t d_indentSpace;
	bool d_needClose;
	bool d_lastIsText;
	OutStream &d_stream;
	std::vector<String> d_tagStack;
	
	void indentLine();

	static String convertEntityInText(const String &text);
	static String convertEntityInAttribute(const String &attributeValue);

	XMLSerializer(const XMLSerializer &obj);
	XMLSerializer& operator=(const XMLSerializer &obj);
};

}