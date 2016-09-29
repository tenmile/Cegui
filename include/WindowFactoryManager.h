#pragma once

#include "Base.h"
#include "String.h"
#include "Singleton.h"
#include "Logger.h"
#include "IteratorBase.h"
#include "Logger.h"
#include "WindowFactory.h"

namespace CEGUI
{

class CEGUIEXPORT WindowFactoryManager: public Singleton<WindowFactoryManager>
{
public:
	struct CEGUIEXPORT FalagardWindowMapping
	{
		String d_windowType;
		String d_lookName;
		String d_baseType;
		String d_effectName
	}

	//class used to track active alias targets for Window Factory types
	class CEGUIEXPORT AliasTargetStack
	{
	public:
		AliasTargetStack(){}
		~AliasTargetStack(){}
		const String& getActiveTarget() const;
		uint getStackedTargetCount() const;
	private:
		friend class WindowFactoryManager;
		typedef std::vector<String> TargetTypeStack;

		TargetTypeStack d_targetStack;
	};
	WindowFactoryManager();
	~WindowFactoryManager()
	{
		Logger::getSingleton().logEvent("CEGUI::WindowFactoryManager singleton destroyed");
	}

	void addFactory(Window* factory);

	template<typename T>
	static void addFactory();

	void removeFactory(const String &name);
	void removeFactory(WindowFactory *factory);
	void removeAllFactories();

	WindowFactory* getFactory(const String &type) const;
	bool isFactoryPresent(const String &name) const;
	void addWindowTypeAlias(const String &aliasName, const String &targeType);
	void removeWindowTypeAlias(const String &aliasName, const String &targetType);
	void addFalagardWindowMapping(const String &newType,
									const String &targetType,
									const String &lookName,
									const String &renderer,
									const String &effectName=String(""));
	void removeFalagardWindowMapping(const String &type);
	bool isFalagardMappedType(const String &type) const;
	const String& getMappedLookForType(const String &type) const;
	const String& getMappedRendererForType(const String &type) const;
	String getDereferencedAliasType(const String &type) const;
	const String& getFalagardMappingForType(const String &type) const;
private:
	typedef std::map<String, WindowFactory*, String::FastLessCompare> WindowFactoryRegistry;
	typedef std::map<String, AliasTargetStack, String::FastLessCompare> TypeAliasRegistry;
	typedef std::map<String, FalagardWindowMapping, String::FastLessCompare> FalagardMapRegistry;

	typedef std::vector<WindowFactory*> OwnedWindowFactoryList;

public:
	typedef ConstBaseIterator<WindowFactoryRegistry>	WindowFactoryIterator;
	typedef ConstBaseIterator<TypeAliasRegistry>		TypeAliasIterator;
	typedef ConstBaseIterator<FalagardMapRegistry>		FalagardMappingIterator;

	WindowFactoryIterator getIterator() const;
	TypeAliasIterator getAliasIterator() const;
	FalagardMappingIterator getFalagardMappingIterator() const;
};

template<typename T>
void WindowFactoryManager::addFactory()
{
	WindowFactory *factory = new T;
	if (WindowFactoryManager::getSingletonPtr())
	{
		Logger::getSingleton().logEvent("Create WindowFactory for '" +factory->getTypeName()+ "' windows.");
		CEGUI_TRY
		{
			WindowFactoryManager::getSingleton().addFactory(factory);
		}
		CEGUI_CATCH(Exception&)
		{
			Logger::getSingleton().logEvent("Deleted WindowFactory for '" +factory->getTypeName()+ "' window.");
			delete factory;
			CEGUI_RETHOW;
		}
	}
	d_ownedFactories.push_back(factory);
}

}