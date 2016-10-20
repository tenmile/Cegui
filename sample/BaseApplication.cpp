#include "BaseApplication.h"
#include "System.h"
#include "DefaultResourceProvider.h"
#include "Imageset.h"
#include "Font.h"
#include "Scheme.h"
#include "WindowManager.h"
#include "falagard/FalWidgetLookManager.h"
#include "ScriptModule.h"
#include "XMLParser.h"
#include "AnimationManager.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CEGUI_SAMPLE_DATAPATH "../datafiles"

const char BaseApplication::DATAPATH_VAR_NAME[] = "CEGUI_SAMPLE_DATAPATH";

const char* BaseApplication::getDataPathPrefix() const
{
	static char dataPathPrefix[PATH_MAX];
	char *envDataPath = 0;
	envDataPath = getenv(DATAPATH_VAR_NAME);
	if(envDataPath!=0)
	{
		strcpy(dataPathPrefix, envDataPath);
	}else
	{
		strcpy(dataPathPrefix, CEGUI_SAMPLE_DATAPATH);
	}

	return dataPathPrefix;
}

void BaseApplication::initialiseResourceGroupDirectories()
{
	CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	const char *dataPathPrefix = getDataPathPrefix();
	char resourcePath[PATH_MAX];

	sprintf(resourcePath, "%s%s", dataPathPrefix, "schemes/");
	rp->setResourceGroupDirectory("schemes", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "imagesets/");
	rp->setResourceGroupDirectory("imagesets", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "fonts/");
	rp->setResourceGroupDirectory("fonts", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "layouts/");
	rp->setResourceGroupDirectory("layouts", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "looknfeels/");
	rp->setResourceGroupDirectory("looknfeels", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "lua_scripts/");
	rp->setResourceGroupDirectory("lua_scripts", resourcePath);
	sprintf(resourcePath, "%s%s", dataPathPrefix, "xml_schemas/");
	rp->setResourceGroupDirectory("xml_schemas", resourcePath);
}

void BaseApplication::initialiseDefaultResourceGroups()
{
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	CEGUI::AnimationManager::setDefaultResourceGroup("animations");

	CEGUI::XMLParser *parser = CEGUI::System::getSingleton().getXMLParser();
	if(parser->isPropertyPresent("SchemaDefaultResourceGroup"))
	{
		parser->setProperty("SchemeDefaultResourceGroup", "schemas");
	}
}