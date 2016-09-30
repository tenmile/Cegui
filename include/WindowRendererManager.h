#pragma once

#include "Singleton.h"
#include "WindowRenderer.h"
#include "Logger.h"
#include "Exceptions.h"
#include <map>
#include <vector>

namespace CEGUI
{

class CEGUIEXPORT WindowRendererManager: public Singleton<WindowRendererManager>
{
public:
	WindowRendererManager();
	~WindowRendererManager();

	static WindowRendererManager& getSingleton();
	static WindowRendererManager* getSingletonPtr();

	bool isFactoryPresent(const String& name) const;
	WindowRendererFactory* getFactory(const String& name) const;


	template<typename T>
	static void addFactory();
	void addFactory(WindowRendererFactory *wr);
	void removeFactory(const String &name);

private:
	typedef std::map<String, WindowRendererFactory*, String::FastLessCompare> WR_Registry;
	WR_Registry d_wrReg;
	typedef std::vector<WindowRendererFactory*> OwnedFactoryList;
	static OwnedFactoryList d_ownedFactories;
};

template<typename T>
void WindowRendererManager::addFactory()
{
	WindowRendererFactory *factory = new T;
	if (WindowRendererManager::getSingletonPtr())
	{
		Logger::getSingleton().logEvent("Create WindowRendererFactory for '" +factory->getName()+ "' WindowRenderer.");
		CEGUI_TRY
		{
			WindowRendererManager::getSingleton().addFactory(factory);
		}
		CEGUI_CATCH
		{
			Logger::getSingleton().logEvent("Delete WindowRendererFactory for '" +factory->getName()+ "' WindowRenderers.");
			delete factory;
			CEGUI_RETHROW;
		}
	}
	d_ownedFactories.push_back(factory);
}

}