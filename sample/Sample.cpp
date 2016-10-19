#include "Sample.h"

#include "config.h"
#include "SamplesConfig.h"

#include "BaseApplication.h"
#include "CEGUI.h"


Sample::Sample():
		d_sampleApp(0){}

Sample::~Sample()
{
	if(d_sampleApp)
	{
		d_sampleApp->cleanup();
		delete d_sampleApp;
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
	d_sampleApp = new D3D9BaseApplication();
	if(d_sampleApp->execute(this))
	{
		return true;
	}
	delete d_sampleApp;
	d_sampleApp = 0;
	return false;
}

void Sample::cleanup()
{
	if(d_sampleApp)
	{
		d_sampleApp->cleanup();
		delete d_sampleApp;
		d_sampleApp = 0;
	}
}

void Sample::outputExceptionMessage(const char *message) const
{
	MessageBoxA(0, message, "CEGUI-Exception", MB_OK | MB_ICONERROR);
}