#pragma once

#include "Base.h"

namespace CEGUI
{

class CEGUIEXPORT XMLHandler
{
public:
	XMLHandler();
	virtual ~XMLHandler();
	virtual void elementStart(const String &element, const XMLAttributes &attributes);
	virtual void elementEnd(const String &element);
	virtual void text(const String &text);
};

}