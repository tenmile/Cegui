#include "Property.h"
#include "XMLSerializer.h"

namespace CEGUI
{

namespace WindowProperties
{

class ID: public Property
{
public:
	ID(): Property(
		"ID",
		"Property to get/set the ID value of the window, Value is an unsigned integer number."
		"0"){}
	String get(const Property *receiver) const;
	void set(PropertyReceiver *receiver, const String &value);
};

}

}