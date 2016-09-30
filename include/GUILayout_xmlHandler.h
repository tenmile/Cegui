#pragma once

#include "WindowManager.h"
#include "Window.h"
#include "XMLHandler.h"

#include <vector>

namespace CEGUI
{

class GUILayout_xmlHandler: public XMLHandler
{
	typedef WindowManager::PropertyCallback PropertyCallback;
public:
	GUILayout_xmlHandler(const String &name_prefix, PropertyCallback *callback=0, void *userdata=0):
		d_root(0),
		d_namePrefix(name_prefix),
		d_propertyCallBack(callback),
		d_userData(userdata){}
	virtual ~GUILayout_xmlHandler();

	virtual void elementStart(const String &element, const XMLAttributes &attribute);
	virtual void elementEnd(const String &element);
	virtual void text(const String &text);

	void cleanupLoadedWindows();

	Window *getLayoutRootWindow() const;

private:
	static const String GUILayoutElement;
	static const String WindowElement;
	static const String AutoWindowElement;
	static const String PropertyElement;
	static const String LayoutImportElement;
	static const String EventElement;
	static const String WindowTypeAttribute;
	static const String WindowNameAttribute;
	static const String AutoWindowNameSuffixAttribute;
	static const String PropertyNameAttribute;
	static const String PropertyValueAttribute;
	static const String LayoutParentAttribute;
	static const String LayoutImportFilenameAttribute;
	static const String LayoutImportPrefixAttribute;
	static const String LayoutImportResourceGroupAttribute;
	static const String EventNameAttribute;
	static const String EventFunctionAttribute;

	void elementGUILayoutStart(const XMLAttributes &attribute);
	void elementWindowStart(const XMLAttributes &attribute);
	void elementAutoWindowStart(const XMLAttributes &attribute);
	void elementPropertyStart(const XMLAttributes &attribute);
	void elementLayoutImportStart(const XMLAttributes &attribute);
	void elementEventStart(const XMLAttributes &attribute);
	void elementGUILayoutEnd();
	void elementWindowEnd();
	void elementAutoWindowEnd();
	void elementPropertyEnd();

	void operator=(const GUILayout_xmlHandler&) {}

	typedef std::pair<Window*, bool> WindowStackEntry;
	typedef std::vector<WindowStackEntry> WindowStack;
	Window *d_root;
	WindowStack d_stack;
	String d_layoutParent;
	const String &d_namingPrefix;
	PropertyCallback *d_propertyCallback;
	void *userdata;
	String d_propertyName;
	String d_propertyValue;

};

}