#include "Base.h"
#include "String.h"
#include "Vector.h"
#include "Rect.h"
#include "Size.h"
#include "EventSet.h"
#include "PropertySet.h"
#include "System.h"
#include "InputEvent.h"
#include "WindowProperties.h"
#include "UDim.h"
#include "WindowRender.h"
#include "TextUtils.h"
#include "BasicRendererdStringParser.h"
#include "DefaultRendererdStringParser.h"
#include <vector>
#include <set>

namespace CEGUI
{

enum VerticalAlignment
{
	VA_TOP,
	VA_CENTER,
	VA_BOTTOM
};
enum HorizontalAlignment
{
	HA_LEFT,
	HA_CENTER,
	HA_RIGHT
};
enum WindowUpdateMode
{
	WUM_ALWAYS,		//Always call the Window::update for this window
	WUM_NEVER,		//never
	WUM_VISIBLE		//if it is visible
};

class CEGUIEXPORT Window: public PropertySet, public EventSet
{
	static const String EventNamespace;		//namespace for global events

	static const String EventWindowUpdate;
	static const String EventParentSized;
	static const String EventSized;
	static const String EventMoved;
	static const String EventTextChanged;
	static const String EventFontChanged;
	static const String EventAlphaChanged;
	static const String EventIDChanged;
	static const String EventActivated;
	static const String EventDeactived;
	static const String EventShown;
	static const String EventHiden;
	static const String EventEnabled;
	static const String EventDisabled;
	static const String EventClippedByParentChanged;
	static const String EventDestroyedByParentChanged;
	static const String EventInheritsAlphaChanged;
	static const String EventAlwaysOnTopChanged;
	static const String EventInputCaptureGained;
	static const String EventInputCaptureLost;
	static const String EventRenderingStarted;
	static const String EventRenderingEnded;
	static const String EventChildAdded;
	static const String EventDestructionStarted;
	static const String EventZOrderChanged;
	static const String EventDragDropItemEnters;


	//widget name suffix for automatically created tooltip widgets.
	static const String TooltipNameSuffix;
	//something that all generated widgets will have in their names.
	static const String AutoWidgetNameSuffix;
	
	Window(const String &type, const String &name);
	virtual ~Window();

	const String &getType() const;
	const String &getName() const {return d_name;}
	bool isDestroyedByParent() const {return d_destroyedByParent;}
	bool isAlwaysOnTop() const {return d_alwaysOnTop;}
	bool isDisabled(bool localOnly=false) const;
	bool isVisible(bool localOny=false) const;
	bool isActive() const;
	bool isClippedByParent() const {return d_clippedByParent;}
	uint getID() const {return d_ID;}
	size_t getChildCount() const {return d_children.size()}
	bool isChild(const String &name) const;
	bool isChild(uint ID) const;
	bool isChildRecursive(uint ID) const;
	bool isChild(const Window *window) const;
	Window* getChild(const String &name) const;
	Window* getChild(uint ID) const;
	Window* getChildRecursive(const String &name) const;
	Window* getChildRecursive(uint ID) const;
	Window* getChildAtIdx(size_t idx) const {return d_children[idx];}
	Window* getActiveChild();
	const Window* getActiveChild() const;
	bool isAncestor(const String &name) const;
	bool isAncestor(uint Id) const;
	bool isAncestor(const Window *window) const;
	Font* getFont(bool useDefault=true) const;
	const String& getText() const {return d_textLogical;}
	const String& getTextVisual() const;
	bool inheritsAlpha() const {return d_inheritsAlpha}
	float getAlpha() const {return d_alpha;}
	float getEffectiveAlpha() const;
	Rect getUnclippedOuterRect() const;
	Rect getUnclippedInnerRect() const;
	Rect getUnclippedRect(const bool inner) const;
	Rect getOuterRectClipper() const;
	Rect getInnerRectClipper() const;
	Rect getClipRect(const bool non_client=false) const;
	Rect getHitTestRect() const;
	Rect getChildWindowContentArea(const bool non_client=false) const;
	virtual Rect getUnclippedInnerRect_impl() const;
	//¾²Ì¬·½·¨
	static Window* getCaptureWindow() {return d_captureWindow;}
	bool isCaputureByThis() const {return getCaptureWindow()==this;}
	bool isCapturedByAncestor() const {return isAncestor(getCaptureWindow());}
	bool isCapturedByChild() const {return isChild(getCaptureWindow());}
	virtual bool isHit(const Vector2 &position, const bool allow_disable=false) const;
	Window* getChildAtPosition(const Vector2 &position) const;
	Window* getTargetChildAtPosition(const Vector2 &position, const bool allow_disabled=false) const;
	Window* getParent() const {return d_parent;}
	const Image* getMouseCursor(bool useDefault=true) const;
	Size getPixelSize() const {return d_pixelSize;}
	void* getUserData() const {return d_userData;}
	bool restoresOldCapture() const {return d_restoreOldCapture;}
	bool isZOrderingEnabled() const;
	bool wantsMutiClickedEvents() const;
	bool isMouseAutoRepeatEnabled() const;
	float getAutoRepeatDelay() const;
	float getAutoRepeatRate() const;
	bool distributesCapturedInputs() const;
	bool isUsingDefaultTooltip() const;
	Tooltip* getTooltip() const;
	String getTooltipType() const;
	const String& getTooltipText() const;
	bool inheritsTooltipText() const;
	bool isRiseOnClickEnabled() const {return d_riseOnClick;}
	bool testClassName(const String& class_name) const {return testClassName_impl(class_name);}
	VerticalAlignment getVerticalAlignment() const {return d_vertAlign;}
	HorizontalAlignment getHorizontalAlignment() const {return d_horzAlign;}
	GeometryBuffer& getGeometryBuffer();
	const String& getLookNFeel() const;
	bool getModalState() const {return (System::getSingleton.getModalTarget()==this);}
	const String& getUserString(const String &name) const;
	bool isUserStringDefined(const String &name) const;
	Window* getActiveSibling();
	Size getParentPixelSize() const;
	float getParentPixelWidth() const;
	float getParentPixelHeight() const;
	bool isMousePassThroughEnabled() const {return d_mousePassThroughEnabled;}
	bool isAutoWindow() const {return d_autoWindow;}
	bool isWritingXMLAllowed() const {return d_allowWriteXML;}
	EventSet::Iterator getEventIterator() const;
	Property::Iterator getPropertyIterator() const;
	bool isDragDropTarget() const;
	void getRenderingContext(RenderingContext &ctx) const;
	virtual void getRenderingContext_impl(RenderingContext &ctx) const;
	RenderingSurface* getRendeingSurface() const;
	RenderingSurface& getTargetRenderingSurface() const;
	bool isUsingAutoRenderingSurface() const;
	const Window* getRootWindow() const;
	Window* getRootWindow() const;
	const Vector3 getRotation() const;
	bool isNonClientWindow() const;
	void rename(const String &new_name);
	virtual void initializeComponents(){}
	void setDestroyedByParent(bool setting);
	void setAlwaysOnTop(bool setting);
	void setEnabled(bool setting);
	void enable() {setEnabled(true);}
	void disable() {setEnabled(false);}
	void setVisible(bool setting);
	void show() {setVisible(true);}
	void hide() {setVisible(false);}
	void deactivate();
	void setClippedByParent(bool setting);
	void setID(uint ID);
	void setText(const String &text);
	void insertText(const String &text, const String::size_type position);
	void appendText(const String &text);
	void setFont(Font *font);
	void setFont(const String &name);
	void addChildWindow(const String &name);
	void addChildWindow(Window *window);
	void removeChildWindow(const String &name);
	void removeChildWindow(Window *window);
	void removeChildWindow(uint ID);
	void moveToFront();
	void moveToBack();
	void moveInFront(const Window* const window);
	void moveBehind(const Window* const window);
	bool captureInput();
	void releaseInput();
	void setRestoreCapture(bool setting);
	void setAlpha(float alpha);
	void setInheritsAlpha(bool setting);
	void invalidate();
	void invalidate(const bool recursive);
	void setMouseCursor(const Image *image);
	void setMouseCursor(MouseCursorImage image);
	void setMouseCursor(const String &imageset, const String &image_name);
	void setUserData(void *user_data) {d_userData = user_data;}
	void setZOrderingEnabled(bool setting);
	void setWantsMultiClickEvents(bool setting);
	void setMouseAutoRepeatEnabled(bool setting);
	void setAutoRepeatDelay(float delay);
	void setAutoRepeatRate(float rate);
	void setDistributesCapturedInputs(bool setting);
	void notifyDragDropItemEnters(DragContainer *item);
	void notifyDragDropItemLeaves(DragContainer *item);
	void notifyDragDropItemDropped(DragContainer *item);

	virtual void destroy();

	void setTooltip();
	void setTooltipType(const String &tooltipType);
	void setTooltipText(const String &tip);
	void setInheritsTooltipText(bool setting);
	void setRiseOnClickEnabled(bool setting) {d_riseOnClick = setting;}
	void setVerticalAlignment(const HorizontalAlignment alignment);

	virtual void setLookNFeel(const String& look);

	void setModalState(bool state);

	virtual void performChildWindowLayout();

	void setUserString(const String &name, const String &value);
	void setArea(const UDim &xpox, const UDim &ypos, const UDim &width, const UDim &height);
	void setArea(const UVector2 &pos, const UVector2 &size);
	void setArea(const URect &area);
	void setPosition(const UVector2 &pos);
	void setXPosition(const UDim &x);
	void setYPosition(const UDim &y);
	void setWidth(const UDim &width);
	void setHeight(const UDim &height);
	void setMaxSize(const UVector2 &size);
	void setMinSize(const UVector2 &size);
	const URect &getArea() const;
	const UVector2 &getPosition() const;
	const UDim& getXPosition() const;
	const UDim& getYPosition() const;
	UVector2 getSize() const;
	UDim getWidth() const;
	UDim getHeight() const;
	const UVector2& getMaxSize() const;
	const UVector2& getMinSize() const;
	void render();

	virtual void update(float elapsed);
	virtual void writeXMLToStream(XMLSerializer &xml_stream) const;
	virtual void beginInitialisation() {d_initialising = true;}
	virtual void endInitialisation() {d_initialising = false;}

	void setMousePassThroughEnabled(bool setting) {d_mousePassThroughEnabled = setting;}
	void setWindowRenderer(const String &name);
	WindowRenderer* getWindowRenderer() const;
	String getWindowRendererName() const;
	void setWritingXMLAllowed(bool allow) {d_allowWriteXML = allow;}
	void notifyScreenAreaChanged(bool recursive=true);
	void setFalagardType(const String &type, const String &rendererType = "");
	void setDragDropTarget(bool setting);
	void setRenderingSurface(RenderingSurface *surface);
	void invalidateRenderingSurface();
	void setUsingAutoRenderingSurface(bool setting);
	void setRotation(const Vector3 &rotation);
	void setNonClientWindow(const bool setting);
	const RenderedString& setNonClientWindow(const bool setting);
	RenderedStringParser* getCustomRenderedStringParser() const;
	void setCustomRenderedStringParser(RenderedStringParser *parser);

	virtual RenderedStringParser& getRenderedStringParser() const;

	bool isTextParsingEnabled() const;
	void setTextParsingEnabled(const bool setting);

	virtual void setMargin(const UBox &margin);

	Vector2 getUnprojectedPosition(const Vector2 &pos) const;
	const BidiVisualMapping* getBidiVisualMapping() const {return d_bidiVisualMapping;}
	void banPropertyFromXML(const String &property_name);
	void unbanPropertyFromXML(const String &propery_name);
	bool isPropertyBannedFromXML(const String &property_name) const;
	void banPropertyFromXML(const Property *property);
	void unbanPropertyFromXML(const Property *property);
	bool isPropertyBannedFromXML(const Property *property) const;
	void setUpdateMode(const WindowUpdateMode mode);
	WindowUpdateMode getUpdateMode() const;
	void setMouseInputPropagationEnabled(const bool enable);
	bool isMouseInputPropagationEnabled() const;
	Window* clone(const String &newName, const bool deepCopy=true) const;

	virtual void clonePropertiesTo(Window &target) const;
	virtual void cloneChildWidgetsToTo(Window &target) const;

	size_t getZIndex() const;

	bool isInFront(const Window &wnd) const;
	bool isBehind(const Window &wnd) const;
protected:
	friend class System;
	friend class WindowManger;
	
	virtual void onSize(WindowEventArgs &e);
	virtual void onMoved(WindowEventArgs &e);
	virtual void onTextChanged(WindowEventArgs &e);
	virtual void onFontChanged(WindowEventArgs &e);
	virtual void onAlphaChanged(WindowEventArgs &e);
	virtual void onIDChanged(WindowEventArgs &e);
	virtual void onShown(WindowEventArgs &e);
	virtual void onHidden(WindowEventArgs &e);
	virtual void onEnabled(WindowEventArgs &e);
	virtual void onDisabled(WindowEventArgs &e);
	virtual void onClippingChanged(WindowEventArgs &e);
	virtual void onParentDestroyChanged(WindowEventArgs &e);
	virtual void onInheritsAlphaChanged(WindowEventArgs &e);
	virtual void onAlwaysOnTopChanged(WindowEventArgs &e);
	virtual void onCaptureGained(WindowEventArgs &e);
	virtual void onCaptureLost(WindowEventArgs &e);
	virtual void onRenderingStarted(WindowEventArgs &e);
	virtual void onRenderingEnded(WindowEventArgs &e);
	virtual void onZChanged(WindowEventArgs &e);




	virtual void updateSelf(float elapsed);
	virtual void drawSelf(const RenderingContext &ctx);

	void bufferGeometry(const RenderingContext &ctx);
	void queueGeometry(const RenderingContext &ctx);

	virtual void populateGeometryBuffer() {}
	virtual bool testClassName_impl(const String &class_name) const
	{
		if (class_name == "Window")
		{
			return true;
		}
		return false;
	}

	void setParent(Window *parent);
	Size getSize_impl(const Window *window) const;
	void generateAutoRepeatEvent(MouseButton button);

	virtual bool validateWindowRenderer(const String &name) const;

	bool isPropertyAtDefault(const Property *property) const;
	void allocateRenderingWindow();
	void initialiseClippers(const RenderingContext &ctx);

	virtual void cleanupChildren();
	virtual void addChild_impl();
	virtual void removeChild_impl(Window *wnd);
	virtual void onZChanged();

	void addStandardProperties();

	virtual bool moveToFront_impl(bool wasClicked);

	void setArea_impl(const UVector2 &pos, const UVector2 &size, bool topLeftSizing=false, bool fireEvents=true);
	void addWindowToDrawList(Window &wnd, bool at_back=false);
	void removeWindowFromDrawList(const Window &wnd);
	bool isTopOfZOrder() const;
	void updateGeometryRenderSettings();
	void transferChildSurfaces();
	Rect getParentElementClipIntersection(const Rect &unclipped_area) const;
	void invalidate_impl(const bool recursive);
	bool isInnerRectSizeChanged() const;
	const Window* getWindowAttachedToCommonAncestor(const Window &wnd) const;

	virtual Rect getUnclippedOuterRect_impl() const;
	virtual Rect getOuterRectClipper_impl() const;
	virtual Rect getInnerRectClipper_impl() const;
	virtual Rect getHitTestRect_impl() const;
	virtual Rect getNonClientChildWindowContentArea_impl() const;
	
	virtual int writePropertiesXML(XMLSerializer &xml_stream) const;
	virtual int writeChildWindowsXML(XMLSerializer &xml_stream) const;
	virtual bool writeAutoChildWindowXML(XMLSerializer &xml_stream) const;

	bool constrainUVector2ToMinSize(const Size &base_sz, UVector2 &sz);
	bool constrainUVector2ToMaxSize(const Size &base_sz, UVector2 &sz);

	static WindowProperties::Alpha						d_alphaProperty;
	static WindowProperties::AlwaysOnTop				d_alwaysOnTop;
	static WindowProperties::ClippedByParent			d_clippedByParent;



	typedef std::vector<Window*> ChildList;
	typedef std::map<String, String, String::FastLessCompare> UserStringMap;
	typedef std::set<String, String::FastLessCompare> BannedXMLPropertySet;

	const String d_type;
	String d_name;
	String d_falagardType;
	bool d_autoWindow;
	bool d_initialising;
	bool d_destructionStarted;
	bool d_enabled;
	bool d_visible;
	bool d_active;

	ChildList d_children;
	ChildList d_drawList;
	Window *d_parent;

	bool d_destroyedByParent;
	bool d_clippedByParent;
	String d_lookName;
	WindowRenderer *d_windowRenderer;
	GeometryBuffer *d_geometry;
	RenderingSurface *d_surface;

	mutable bool d_needsRedraw;
	const Image *d_mouseCursor;

	float d_alpha;
	bool d_inheritsAlpha;

	static Window *d_captureWindow;
	Window *d_oldCapture;
	bool d_restoreOldCapture;
	bool d_distCapturedInputs;

	Font *d_font;
	String d_textLogical;
	BidiVisualMapping *d_bidiVisualMapping;

	mutable bool d_bidiVisualMapping;
	mutable RenderedString d_renderedString;
	mutable bool d_renderedStringValid;

	static BasicRenderedStringParser d_basicStringParser;
	static DefaultRenderedStringParser d_defaultStringParser;
	RenderedStringParser *d_customStringParser;
	bool d_textParsingEnabled;
	UBox d_textParsingEnabled;
	unit d_ID;
	void *d_userData;
	UserStringMap d_userStrings;

	bool d_alwaysOnTop;
	bool d_riseOnClick;
	bool d_zOrderingEnabled;
	bool d_wantsMultiClicks;



};

}