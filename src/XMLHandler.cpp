#include "XMLHandler.h"

namespace CEGUI
{

XMLHandler::XMLHandler() {}
XMLHandler::~XMLHandler() {}
void XMLHandler::elementStart(const String&, const XMLAttributes&){}
void XMLHandler::elementEnd(const String&) {}
void XMLHandler::text(const String&) {}

}