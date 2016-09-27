#pragma once

#include "Base.h"
#include "String.h"
#include "XMLSerializer.h"

namespace CEGUI
{

class CEGUIEXPORT PropertyReceiver
{
public:
	PropertyReceiver(){}
	virtual ~PropertyReceiver(){}
};

class CEGUIEXPORT Property
{
public:
	Property(const String &name, const String &help, const String &defaultValue="", bool writeXML = true):
		d_name(name),
		d_help(help),
		d_default(defaultValue),
		d_writeXML(writeXML){}
	virtual ~Property(){}

	const String& getHelp()const
	{
		return d_help;
	}
	const String& getName()const
	{
		return d_name;
	}

	virtual String get(const Property *receiver) const = 0;
	virtual void set(PropertyReceiver *receiver, const String &value) = 0;

	virtual bool isDefault(const PropertyReceiver *receiver) const;
	virtual String getDefault(const PropertyReceiver *receiver) const;
	virtual void writeXMLToStream(const PropertyReceiver *receiver, XMLSerializer &xml_stream) const;
protected:
	String d_name;
	String d_help;
	String d_default;
	bool d_writeXML;
			
};

}