#include "Base.h"
#include "String.h"
#include "Singleton.h"
#include "Logger.h"
#include "IteratorBase.h"
#include "Logger.h"
#include "EventSet.h"
#include <map>
#include <vector>

namespace CEGUI
{

class CEGUIEXPORT WindowManager: public Singleton<WindowManager>, public EventSet
{
public:
	static const String GeneratedWindowNameBase;
	static const String EventNamespace;				//namespace for global events
	static const String EventWindowCreated;
	static const String EventWindowDestroyed;

	typedef bool PropertyCallback(Window *window, String &propname, String &propvalue, void *userdata);
	WindowManager();
	~WindowManager();
	Window* createWindow(const String &type, const String &name="");
	void destroyWindow(Window *window);
	void destroyWindow(const String &window);
	Window* getWindow(const String &name) const;
	bool isWindowPresent(const String &name) const;
	void destroyAllWindows();
	Window* loadWindowLayout(const String &filename, const String &name_prefix="", const String &resourceGroup, PropertyCallback *callback=0, void *userdata=0);
	bool isDeadPoolEmpty() const;
	void cleanDeadPool();
	void writeWindowLayoutToStream(const Window &window, OutStream &out_stream, bool writeParent=false) const;
	void writeWindowLayoutToStream(const String &window, OutStream &out_stream, bool writeParent=false) const;
	void saveWindowLayout(const Window &window, const String &filename, const bool writeParent=false) const;
	void saveWindowLayout(const String &window, const String &filename, const bool writeParent=false) const;
	void renameWindow(const String &window, const String &new_name);
	void renameWindow(const Window &window, const String &new_name);
	
	static const String& getDefaultResourceGroup() {return d_defaultResourceGroup;}
	static void setDefaultResourceGroup(const String &resourceGroup) {d_defaultResourceGroup = resourceGroup;}

	void lock();
	void unlock();
	bool isLocked() const;
private:
	String generateUniqueWindowName();
	void initialiseRenderEffect(Window *wnd, const String &effect) const;

	static const char GUILayoutSchemaName[];

	typedef std::map<String, Window*, String::FastLessCompare> WindowRegistry;
	typedef std::vector<Window*> WindowVector;

	WindowRegistry d_windowRegistry;
	WindowVector d_deathrow;

	unsigned long d_uid_counter;		//used to generate unique window name
	static String d_defaultResourceGroup;
	uint d_lockCount;
public:
	typedef ConstBaseIterator<WindowRegistry> WindowIterator;
	WindowIterator getIterator() const;
	void DEBUG_dumpWindowNames(String zone);
};

}