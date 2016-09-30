#pragma once

#include "Base.h"
#include "String.h"
#include "Singleton.h"
#include "Renderer.h"
#include "MouseCursor.h"
#include "InputEvent.h"
#include "ResourceProvider.h"

namespace CEGUI
{

stuct MouseClickTrackerImpl;

class CEGUIEXPORT System: public Singleton<System>, public EventSet
{
public:
	static const String EventNamespace;		//namespace for gloabal events
	
	static const double		DefaultSingleClickTimeout;
	static const double		DefaultMultiClickTimeout;
	static const Size		DefaultMutiClickAreaSize;

	static const String EventGUISheetChanged;
	static const String EventSingleClickTimeoutChanged;
	static const String EventMultiClickTimeoutChanged;
	static const String EventMultiClickAreaSizeChanged;
	static const String EventDefaultFontChanged;
	static const String EventDefaultMouseCursorChanged;
	static const String EventMouseMoveScalingChanged;
	static const String EventDisplaySizeChanged;
	static const String EventRenderedStringParserChanged;

	static System& create(Renderer& renderer,
							ResourceProvider *resourceProvider=0,
							XMLParser *XMLParser=0,
							ImageCodec *imageCodec=0,
							ScriptModule *scriptModule=0,
							const String *configFile="",
							const Sring &logFile="CEGUI.log");
	static void destroy();
	Renderer* getRenderer() const {return d_renderer;}

	static System& getSingleton();
	static System* getSingletonPtr();

	void setDefaultFont(const String &name);
	void setDefaultFont(Font *font);
	Font* getDefaultFont() const {return d_defaultFont;}
	void signalRedraw() {d_gui_redraw = true;}
	bool isRedrawRequested() const {return d_gui_redraw;}
	void rendererGUI();
	Window* setGUISheet(Window *sheet);
	Window* getGUISheet() const {return d_activeSheet;}
	double getSingleClickTimeout() const {return d_click_timeout;}
	double getMultiClickTimeout() const {return d_dblclick_timeout;}
	const Size& getMultiClickToleranceAreaSize() const {return d_dblclick_size;}
	void setSingleClickTimeout(double timeout);
	void setMultiClickTimeout(double timeout);
	void setMultiClickToleranceAreaSize(const Size& sz);
	bool isMouseClickEventGenerationEnable() const;
	void setMouseClickEventGenerationEnabled(const bool enable);
	const Image* getDefaultMouseCursor() const {return d_defaultMouseCursor;}
	void setDefaultMouseCursor(const Image *image);
	void setDefaultMouseCursor(MouseCursorImage image) {setDefaultMouseCursor((const Image*)image);}
	void setDefaultMouseCursor(const String &imageset, const Sring &image_name);
	Window* getWindowContainingMouse() const {return d_wndWithMouse;}
	ScriptModule* getScriptingModule() const;
	void setScriptingModule(ScriptModule * scriptModule);
	ResourceProvider* getResourceProvider() const;
	void executeScriptFile(const String &filename, const Sring &resourceGroup="") const;
	int executeScriptGlobal(const String &function_name) const;
	void executeScriptString(const Sring &str) const;
	float geMouseMoveScaling() const;
	void getMouseMoveScaling(float scaling);
	void notifyWindowDestroyed(const Window *window);
	uint getSystemKeys() const {return d_sysKeys;}
	void setXMLParser(const String &parserName);
	void setXMLParser(XMLParser *parser);
	XMLParser* getXMLParser() const {return d_xmlParser;}
	void setDefaultTooltip(Tooltip *tooltip);
	void setDefaultTooltip(const String &tooltipType);
	Tooltip* getDefaultTooltip() const;
	void setModalTarget(Window *target) {d_modalTarget = target;}
	Window* getModalTarget() const {return d_modalTarget;}

	static void setDefaultXMLParserName(const String &parserName);
	static const String getDefautlXMLParerName();

	bool updateWindowContainingMouse();
	ImageCodec& getImageCodec() const;
	void setImageCodec(const String &codecName);
	void setImageCodec(ImageCodec &codec);

	static void setDefaultImageCodecName(const String &codecName);
	static const String getDefaultImageCodecName();

	void notifyDisplaySizeChanged(cosnt Size &new_size);
	RenderedStringParser* getDefaultCustomRenderedStringParser() const;
	void setDefaultCustomRenderedStringParser(RenderedStringParser *parser) const;
	void invalidateAllCachedRendering();
	bool injectMouseMove(float delta_x, float delta_y);
	bool injectMouseLeave();
	bool injectMouseButtonDown(MouseButton button);
	bool injectMouseButtonUp(MouseButton button);
	bool injectKeyDown(uint key_code);
	bool injectKeyUp(uint key_code);
	bool injectChar(uint32 code_point);
	bool injectMouseWheelChange(float delta);
	bool injectMousePosition(float x_pos, float y_pos);
	bool injectTimePulse(float timeElapsed);
	bool injectMouseButtonClick(const MouseButton button);
	bool injectMouseButtonDoubleClick(const MouseButton button);
	bool injectMouseButtonTripleClick(const MouseButton button);
private:
	System(const System &obj);
	System& operator=(const System &obj);
	System(Renderer &renderer, ResourceProvider *resourceProvider,
					XMLParser *xmlParser, ImageCodec *imageCodec,
					ScriptModule *scriptModule, const String &configFile,
					const String &logFile);
	~System();
	Window* getTargetWindow(const Point &pt, const bool allow_disabled) const;
	Window* getKeyboardTargetWindow() const;
	Window* getNextTargetWindow(Window *w) const;
	SystemKey mouseButtonToSyskey(MouseButton btn) const;
	SystemKey keyCodeToSyskey(Key::Scan key, bool direction);
	void outputLogHeader();
	void addStandardWindowfactories();
	void createSingletons();
	void destroySingletons();
	void setupXMLParser();
	void cleanupXMLParser();
	bool mouseMoveInjection_impl(MouseEventArgs &ma);
	void setupImageCodec(const String &codecName);
	void cleanupImageCodec();
	void initialiseVersionString();
	void invalidateAllWindow();
	Window* getCommonAncestor(Window *w1, Window *w2);
	void notifyMouseTransaction(Window *top, Window *button, void(Window::func)(MouseCursorEventArgs&), MouseEventArgs& args);
	void createSystemOwnedDefaultTooltipWindow() const;
	void destroySystemOwnedDefaultTooltipWindow();
	
	void onGUISheetChanged(WindowEventArgs &e);
	void onSingleClickTimeoutChanged(EventArgs &e);
	void onMultiClickTimeoutChanged(EventArgs &e);
	void onMultiClickAreaSizeChanged(EventArgs &e);
	void onDefaultFontChanged(EventArgs &e);
	void onDefaultMouseCursorChanged(EventArgs &e);
	void onMouseMoveScalingChanged(EventArgs &e);


	Renderer *d_renderer;
	ResourceProvider *d_resourceProvider;
	bool d_ourResourceProvider;
	Font *d_defaultFont;
	bool d_gui_redraw;

	Window *d_wndWithMouse;
	Window *d_activeSheet;
	Window *d_modalTarget;

	String d_strVersion;

	uint d_sysKeys;
	bool d_lshift;
	bool d_rshift;
	bool d_lctrl;
	bool d_rctrl;
	bool d_lalt;
	bool d_ralt;

	double	d_click_timeout;
	double	d_dbclick_timeout;
	Size	d_dbclick_size;

	MouseClickTrackerImpl* const d_clickTrackerPimpl;
	const Image *d_defaultMouseCursor;
	ScriptModule *d_scriptModule;
	String d_termScriptName;
	float d_mouseScalingFactor;
	XMLParser *d_xmlParser;
	bool d_ourXmlParser;
	DynamicModule *d_parserModule;

	mutable Tooltip *d_defaultToolTip;
	mutable bool d_weOwnTooltip;
	String d_defaultTooltipType;
	static String d_defaultXMLParserName;
	ImageCodec *d_imageCodec;
	bool d_ourImageCodec;
	DynamicModule *d_imageCodecModule;
	static String d_defaultImageCodecName;
	RenderedStringParser *d_customRenderedStringParser;
	bool d_generateMouseClickEvent;
};

}