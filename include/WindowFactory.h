#pragma once

#include "Base.h"
#include "String.h"
#include "Window.h"

#define CEGUI_DECLARE_WINDOW_FACTORY(T)\
class T ## Factory: public WindowFactory\
{\
public:\
	T ## Factory(): WindowFactory(T::WidgetTypeName) {}\
	{\
		return new T (type, name);\
	}\
	void destrotyWindow(Window *window)\
	{\
		delete window;\
	}\
};\
T ## Factory& get ## T ## Factory();

#define CEGUI_DEFINE_WINDOW_FACTORY(T)\
T ## Factory& get ## T ## Factory()\
{\
	static T ## Factory s_factory;\
	return s_factory;\
}\

#define CEGUI_WINDOW_FACTORY(T) (get ## T ## Factory()

namespace CEGUI
{
public:
	virtual Window* createWindow(const String &name) = 0;
	virtual void destroyWindow(Window *window) = 0;
	const String& getTypeName() const {return d_type;}
	virtual ~WindowFactory();
protected:
	WindowFactory(const String &type): d_type(type) {}
	String d_type;
}