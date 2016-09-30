#include "GUILayout_xmlHandler.h"
#include "Exceptions.h"
#include "System.h"
#include "ScriptModule.h"
#include "XMLAttributes.h"

namespace CEGUI
{

const String GUILayout_xmlHandler::GUILayoutElement("GUILayout");
const String GUILayout_xmlHandler::WindowElement("Window");
const String GUILayout_xmlHandler::AutoWindowElement("AutoWindow");
const String GUILayout_xmlHandler::PropertyElement("Property");
const String GUILayout_xmlHandler::LayoutImportElement("LayoutImport");
const String GUILayout_xmlHandler::EventElement("Event");
const String GUILayout_xmlHandler::WindowTypeAttribute("Type");
const String GUILayout_xmlHandler::WindowNameAttribute("Name");
const String GUILayout_xmlHandler::AutoWindowNameSuffixAttribute("NameSuffix");
const String GUILayout_xmlHandler::PropertyNameAttribute("Name");
const String GUILayout_xmlHandler::PropertyValueAttribute("Value");
const String GUILayout_xmlHandler::LayoutParentAttribute("Parent");
const String GUILayout_xmlHandler::LayoutImportFilenameAttribute("Filename");
const String GUILayout_xmlHandler::LayoutImportPrefixAttribute("Prefix");
const String GUILayout_xmlHandler::LayoutImportResourceGroupAttribute("ResourceGroup");
const String GUILayout_xmlHandler::EventNameAttribute("Name");
const String GUILayout_xmlHandler::EventFunctionAttribute("Function");

void GUILayout_xmlHandler::elementStart(const String &element, const XMLAttributes &attribute)
{
	if (element == GUILayoutElement)
	{
		elementGUILayoutStart(attribute);
	}else if (element == WindowElement)
	{
		elementWindowStart(attribute);
	}else if (element == AutoWindowElement)
	{
		elementAutoWindowStart(attribute);
	}else if (element == PropertyElement)
	{
		elementPropertyStart(attribute);
	}else if (element == LayoutImportElement)
	{
		elementLayoutImportStart(attribute);
	}else if (element == EventElement)
	{
		elementEventStart(attribute);
	}else
	{
		Logger::getSingleton().logEvent("GUILayout_xmlHandler::startElement - Unexpected data was found while parsing the gui-layout file: '" +element+ "' is unknown.");
	}
}

void GUILayout_xmlHandler::elementEnd(const String &element)
{
	if (element == GUILayoutElement)
	{
		elementGUILayoutEnd();
	}else if (element == WindowElement)
	{
		elementWindowEnd();
	}else if (element == AutoWindowElement)
	{
		elementAutoWindowEnd();
	}else if (element == PropertyElement)
	{
		elementPropertyEnd();
	}
}

void GUILayout_xmlHandler::text(const String &text)
{
	d_propertyValue += text;
}

void GUILayout_xmlHandler::cleanupLoadedWindows()
{
	while (!d_stack.empty())
	{
		if (d_stack.back().second)
		{
			Window *wnd = d_stack.back().first;
			if (wnd->getParent())
			{
				wnd->getParent()->removeChildWindow(wnd);
			}
			d_stack.pop_back();
		}
	}

	d_root = 0;
}

Window* GUILayout_xmlHandler::getLayoutRootWindow() const
{
	return d_root;
}

void GUILayout_xmlHandler::elementGUILayoutStart(const XMLAttributes &attributes)
{
	d_layoutParent = attributes.getValueAsString(LayoutParentAttribute);
	if (!d_layoutParent.empty())
	{
		if (!WindowManager::getSingleton().isWindowPresent(d_layoutParent))
		{
			CEGUI_THROW(InvalidRequestException("GUILayout_xmlHandler::startElement - layout loading has been aborted since the specified parent Window ('" +d_layoutParent+ "') does not exist."));
		}
	}
}

void GUILayout_xmlHandler::elementWindowStart(const XMLAttributes &attributes)
{
	String windowType(attributes.getValueAsString(WindowTypeAttribute));
	String windowName(attributes.getValueAsString(WindowNameAttribute));
	CEGUI_TRY
	{
		Window *wnd = WindowManager::getSingleton().createWindow(windowType, d_namingPrefix+windowName);

		if (!d_stack.empty())
		{
			d_stack.back().first->addChildWindow(wnd);
		}else
		{
			d_root = wnd;
		}
		d_stack.push_back(WindowStackEntry(wnd, true));
		wnd->beginInitialisation();
	}
	CEGUI_CATCH(AlreadyExistsException&)
	{
		cleanupLoadedWindows();
		CEGUI_THROW(InvalidRequestException("GUILayout_xmlHandler::startElement - layout loading has been aborted since Window named '" +windowName+ "' already exists."));
	}
	CEGUI_CATCH(UnknownObjectException&)
	{
		cleanupLoadedWindows();
		CEGUI_THROW(InvalidRequestException("GUILayout_xmlHandler::startElement - layout loading has been aborted since no WindowFactory is availabe for '" +windowType+ "' objects."));
	}
}

}