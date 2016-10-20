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

bool D3D9BaseApplication::execute(Sample *sampleApp)
{
	sampleApp->initialiseSample();
	bool idle;
	HRESULT coop;
	while(Win32AppHelper::doWin32Events(idle))
	{
		if(idle)
		{
			CEGUI::System &guiSystem = CEGUI::System::getSingleton();

			DWORD thisTime = GetTickCount();
			float elapsed = static_cast<float>(thisTime-d_lastFrameTime);
			d_lastFrameTime = thisTime;
			guiSystem.injectTimePulse(elapsed/1000.0f);
			coop = pimpl->d_3DDevice->TestCooperativeLevel();
			if(coop == D3DERR_DEVICELOST)
			{
				Sleep(500);
				continue;
			}else if(coop == D3DERR_DEVICENOTRESET)
			{
				if(!resetDirect3D())
				{
					continue;
				}
			}
			doFPSUpdate();
			static float rot = 0.0f;
			d_logo_geometry->setRotation(CEGUI::Vector3(rot, 0, 0));
			rot += 180.0f*(elapsed/1000.0f);
			if(rot>360.0f)
			{
				rot -= 360.0f;
			}
			Win32AppHelper::doDirectInputEvents(pimpl->d_directInput);
			if(FAILED(pimpl->d_3DDevice->BeginScene()))
			{
				continue;
			}
			pimpl->d_3DDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0.0,0), 1.0f, 0);
			guiSystem.rendererGUI();
			pimpl->d_3DDevice->EndScene();
			pimpl->d_3DDevice->Present(0, 0, 0, 0);
		}
		if(isQuitting())
		{
			PostQuitMessage(0);
		}
	}
	return true;
}

void D3D9BaseApplication::cleanup()
{

}

bool D3D9BaseApplication::initialiseDirect3D(unsigned int width, unsigned int height, unsigned int adapter, bool windowed)
{
	pimpl->d_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(pimpl->d_D3D)
	{
		D3DDISPLAYMODE d3ddm;
		pimpl->d_D3D->GetAdapterDisplayMode(adapter, &d3ddm);
		D3DFORMAT format = d3ddm.Format;
		ShowWindow(pimpl->d_window, SW_NORMAL);
		UpdateWindow(pimpl->d_window);

		ZeroMemory(&pimpl->d_ppars, sizeof(pimpl->d_ppars));
		pimpl->d_ppars.BackBufferFormat = format;
		pimpl->d_ppars.hDeviceWindow = pimpl->d_window;
		pimpl->d_ppars.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pimpl->d_ppars.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		pimpl->d_ppars.Windowed = windowed;

		if(!windowed)
		{
			pimpl->d_ppars.BackBufferWidth = width;
			pimpl->d_ppars.BackBufferHeight = height;
			pimpl->d_ppars.BackBufferCount = 1;
			pimpl->d_ppars.MultiSampleType = D3DMULTISAMPLE_NONE;
			pimpl->d_ppars.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		if(SUCCEEDED(pimpl->d_D3D->CreateDevice(adapter, D3DDEVTYPE_HAL, pimpl->d_window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pimpl->d_ppars, &pimpl->d_3DDevice)))
		{
			return true;
		}else
		{
			MessageBox(0, Win32AppHelper::CREATE_D3D_ERROR, Win32AppHelper::APPLICATION, MB_ICONERROR|MB_OK);
		}

		return false;
	}
}

bool D3D9BaseApplication::resetDirect3D()
{
	pimpl->d_renderer->preD3DReset();
	if(SUCCEEDED(pimpl->d_3DDevice->Reset(&pimpl->d_ppars)))
	{
		pimpl->d_renderer->postD3DReset();
		return true;
	}

	return false;
}

BOID D3D9BaseApplication::doFPSUpdate()
{
	++d_fps_frames;

	DWORD thisTime = GetTickCount();
	if(thisTime-d_fps_lastTime>=1000)
	{
		sprintf(d_fps_textbuff, "FPS: %d", d_fps_frames);
		d_fps_value = d_fps_frames;
		d_fps_frames = 0;
		d_fps_lastTime = thisTime;
	}
}