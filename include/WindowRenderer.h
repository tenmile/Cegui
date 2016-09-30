#include "Window.h"
#include "Property.h"
#include <vector>
#include <utility>

namespace CEGUI
{

class CEGUIEXPORT WindowRenderer
{
public:
	WindowRenderer(const String &name, const String &class_name="Window");
	virtual ~WindowRenderer();

	virtual void render() = 0;

	const String& getName() const {return d_name;}
	Window* getWindow() const {return d_window;}
	const String& getClass() const {return d_class;}
	const WidgetLookFeel& getLookNFeel() const;
	virtual Rect getUnclippedInnerRect() const;
	virtual void performChildWindowLayout() {}
	virtual void getRenderingContext(RenderingContext &ctx) const;
	virtual void update(float) {}
protected:
	void registerProperty(Property *property, const bool ban_from_xml);
	void registerProperty(Property *property);

	virtual void onAttach();
	virtual void onDetach();
	virtual void onLookNFeelAssigned();
	virtual void onLookNFeelUnassigned();

	void operator=(const WindowRenderer&) {}

	Window *window;
	const String d_name;
	const String d_class;

	typedef std::pair<Property*, bool> PropertyEntry;
	typedef std::vector<PropertyEntry> PropertyList;
	PropertyList d_properties;

	friend class Window;
};

class CEGUIEXPORT WindowRendererFactory
{
public:
	WindowRendererFactory(const String &name): d_factoryName(name) {}
	virtual ~WindowRendererFactory(){}

	const String &getName() const {return d_factoryName;}

	virtual WindowRenderer* create() = 0;
	virtual void destroy(WindowRenderer *wr) = 0;
protected:
	String d_factoryName;
};

}