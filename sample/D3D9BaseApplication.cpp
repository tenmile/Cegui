#include "config.h"

#include "D3D9BaseApplication.h"

#include <d3d9.h>
#include <dinput.h>

#include "RendererModules/Direct3D9/Direct3D9Renderer.h"
#include "Sample.h"
#include "Win32AppHelper.h"
#include "CEGUI.h"
#include "RenderingRoot.h"
#include <stdexcept>

struct BaseApplicationImpl
{
	HWND d_window;
	LPDIRECT3D9 d_D3D;
	LPDIRECT3DDEVICE9 d_3DDevice;
	D3DPRESENT_PARAMETERS d_ppars;
	CEGUI::Direct3D9Renderer *d_renderer;
	Win32AppHelper::DirectInputState d_directInput;
};

D3D9BaseApplication::D3D9BaseApplication():
	pimpl(new BaseApplicationImpl),
	d_lastFrameTime(GetTickCount()),
	d_fps_lastTime(d_lastFrameTime),
	d_fps_frames(0),
	d_fps_value(0)
{
	if(pimpl->d_window = Win32AppHelper::createApplicationWindow(800, 600))
	{
		if(initialiseDirect3D(800, 600, D3DADAPTER_DEFAULT, true))
		{
			if(Win32AppHelper::initialiseDirectInput(pimpl->d_window, pimpl->d_directInput))
			{
				pimpl->d_renderer = &CEGUI::Direct3D9Renderer::bootstrapSystem(pimpl->d_3DDevice);
				initialiseResourceGroupDirectories();
				initialiseDefaultResourceGroups();

				CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

				const CEGUI::Rect scrn(CEGUI::Vector2(0,0), pimpl->d_renderer->getDisplaySize());
				d_fps_geometry = &pimpl->d_renderer->createGeometryBuffer();
				d_fps_geometry->setClippingRegion(scrn);

				CEGUI::ImagesetManager::getSingleton().createFromImageFile("cegui_logo", "logo.png", "imagesets");
				d_logo_geometry = &pimpl->d_renderer->createGeometryBuffer();
				d_logo_geometry->setClippingRegion(scrn);
				d_logo_geometry->setPivot(CEGUI::Vector3(50, 34.75f, 0));
				d_logo_geometry->setTranslation(CEGUI::Vector3(10, 520, 0));
				CEGUI::ImagesetManager::getSingleton().get("cegui_logo").getImage("full_iamge").draw(*d_logo_geometry, CEGUI::Rect(0, 0, 100, 69.5f), 0);
				pimpl->d_renderer->getDefaultRenderingRoot().clearGeometry(CEGUI::RQ_OVERLAY);
				pimpl->d_renderer->getDefaultRenderingRoot().subscribeEvent(CEGUI::RenderingSurface::EventRenderQueueStarted, CEGUI::Event::Subscriber(&D3D9BaseApplication::overlayHandler, this));
				return;
			}
			pimpl->d_3DDevice->Release();
			pimpl->d_D3D->Release();
		}
		DestroyWindow(pimpl->d_window);
	}else
	{
		MessageBox(0, Win32AppHelper::CREATE_WINDOW_ERROR, Win32AppHelper::APPLICATION_NAME, MB_ICONERROR|MB_OK);
	}

	CEGUI_THROW(std::runtime_error("Win32 DirectX 9 application failed to initialise."));
}

D3D9BaseApplication::~D3D9BaseApplication()
{
	Win32AppHelper::moveLeaves();
	CEGUI::Direct3D9Renderer::destroySystem();

	Win32AppHelper::cleanDirectInput(pimpl->d_directInput);

	pimpl->d_3DDevice->Release();
	pimpl->d_D3D->Release();

	DestroyWindow(pimpl->d_window);
	delete pimpl;
}

bool D3D9BaseApplication::overlayHandler(const CEGUI::EventArgs &args)
{
	using namespace CEGUI;
	if(static_cast<const RenderQueueEventArgs&>(args).queueID != RQ_OVERLAY)
	{
		return false;
	}

	Font *fnt = System::getSingleton().getDefaultFont();
	if(fnt)
	{
		d_fps_geometry->reset();
		fnt-DrawText(*d_fps_geometry, d_fps_textbuff, Vector2(0,0), 0, colour(0xFFFFFFFF));
		d_fps_geometry->draw();
	}
	d_logo_geometry->draw();
	return true;
}