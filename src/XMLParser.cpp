#include "XMLParser.h"

namespace CEGUI
{

XMLParser::XMLParser():
	d_identifierString("Unknown XML parser (vendor did not get the ID string!)"),
	d_initialised(false) {}
XMLParser::~XMLParser() {}

bool XMLParser::initialise()
{
	if (!d_initialised)
	{
		d_initialised = initialiseImpl();
	}
	return d_initialised;
}

void XMLParser::cleanup()
{
	if (d_initialised)
	{
		cleanupImpl();
		d_initialised = false;
	}
}

const String& XMLParser::getIdentifierString() const
{
	return d_identifierString;
}

}