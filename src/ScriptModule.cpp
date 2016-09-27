#include "ScriptModule.h"
#include "System.h"
#include "Logger.h"
#include "String.h"

namespace CEGUI
{

String ScriptModule::d_defaultResourceGroup;

ScriptModule::ScriptModule():
	d_identifierString("Unknown scipting module(vendor did not set the ID string)")
{}

const String& ScriptModule::getIdentifiedString() const
{
	return d_identifierString;
}

bool ScriptFunctor::operator()(const EventArgs &e) const
{
	ScriptModule *scriptModule = System::getSingleton().getScriptingModule();
	if (scriptModule)
	{
		return scriptModule->excuteScriptedEventHandler(scriptFunctionName, e);
	} 
	else
	{
		Logger::getSingleton().logEvent("Scripted event handler '"+scriptFunctionName+"' could not be called as no ScriptModule is available.", Errors);
		return false;
	}
}

}