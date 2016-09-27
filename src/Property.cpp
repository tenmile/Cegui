#include "Property.h"
#include <iostream>

namespace CEGUI
{

bool Property::isDefault(const PropertyReceiver *receiver)const
{
	return get(receiver) == d_default;
}
String Property::getDefault(const PropertyReceiver*)const
{
	return d_default;
}
void Property::writeXMLToStream(const PropertyReceiver *receiver, XMLSerializer &xml_stream) const
{
	if (d_writeXML)
	{
		xml_stream.openTag("Property").attribute("Name", d_name);
		const String &value = get(receiver);
		if (value.find((urf32)'\n') != String::npos)
		{
			xml_stream.text(value);
		} 
		else
		{
			xml_stream.attribute("Value", get(receiver));
		}
		xml_stream.closeTag();
	}
}

}