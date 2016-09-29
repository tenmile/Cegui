#include "Base.h"
#include "String.h"
#include "PropertySet.h"

namespace CEGUI
{

class CEGUIEXPORT XMLParser: public PropertySet
{
public:
	XMLParser();
	virtual ~XMLParser();
	bool initialise();
	void cleanup();

	virtual void parseXMLFile(XMLHandler &handler, const String &filename, const String &schemeName, const String &resourceGroup) = 0;
	const String& getIdentifierString() const;
protect:
	virtual bool initialiseImpl() = 0;
	virtual void cleanupImpl() = 0;

	String d_identifierString;
private:
	bool d_initialised;
};

}