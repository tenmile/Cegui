#include "Sample.h"

#include "config.h"
#include "SamplesConfig.h"

#include "BaseApplication.h"
#include "CEGUI.h"


Sample::Sample():
		d_rendererSelector(0),
		d_sampleApp(0){}

Sample::~Sample()
{
	if(d_sampleApp)
	{
		d_sampleApp->cleanup();
		delete d_sampleApp;
	}
	if(d_rendererSelector)
	{
		delete d_rendererSelector;
	}
}

int Sample::run()
{
	CEGUI_TRY
	{
		if(initialise())
		{
			cleanup();
		}
		CEGUI_CATCH(CEGUI::Exception &exc)
		{
			outputExceptionMessage(exc.getMessage().c_str());
		}
		CEGUI_CATCH(std::exception &exc)
		{
			outputExceptionMessage(exc.what());
		}
		CEGUI_CATCH(const char *exc)
		{
			outputExceptionMessage(exc);
		}
		CEGUI_CATCH(...)
		{
			outputExceptionMessage("Unknown exception was caught!");
		}
		return 0;
	}
}

bool Sample::initialise()
{
	d_rendererSelector = new Win32RendererSelector;
	d_rendererSelector->setRendererAvailability(Direct3D9GuiRendererType);
}