#pragma once

#include "Base.h"
#include "String.h"
#include "Event.h"

namespace CEGUI
{

class CEGUIEXPORT ScriptModule
{
public:
	ScriptModule();
	virtual ~ScriptModule();
	//Abstract interface
	virtual void excuteScriptFile(const String &filename, const String &resourceGroup="")=0;
	virtual int excuteScriptGlobal(const String &function_name)=0;
	virtual bool excuteScriptedEventHandler(const String &handler_name, const EventArgs &e)=0;
	virtual void excuteString(const String &str)=0;
	//��ʼ��ʱ����
	virtual void createBindings(){}
	virtual void destroyBindings(){}
	//�ű�ģ��ı�ʶ����Ĭ��"Unknown scripting module"
	const String& getIdentifiedString() const;
	//���name�����ڣ��׳��쳣UnkownObjectException
	virtual Event::Connection subscribeEvent(EventSet *target, const String &name, const String &subscriber_name)=0;
	virtual Event::Connection subscribeEvent(EventSet *target, const String &name, Event::Group group, String &subscriber_name)=0;
	static void setDefaultResourceGroup(const String &resourceGroup)
	{
		d_defaultResourceGroup = resourceGroup;
	}
	static const String& getDefaultResourceGroup()
	{
		return d_defaultResourceGroup;
	}
protected:
	String d_identifierString;
	static String d_defaultResourceGroup;
};

class CEGUIEXPORT ScriptFunctor
{
public:
	ScriptFunctor(const String &functionName)
		scriptFunctionName(functionName){}
	ScriptFunctor(const ScriptFunctor &obj):
		scriptFunctionName(obj.scriptFunctionName()){};
	bool operator()(const EventArgs &e) const;
private:
	ScriptFunctor& operator=(const ScriptFunctor &rhs);
	const String scriptFunctionName;
};

}