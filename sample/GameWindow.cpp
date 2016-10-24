#include "GameWindow.h"
#include <tchar.h>
#include <iostream>
using namespace std;

const TCHAR GameWindow::APPLICATION_NAME[] = _TEXT("GameWindow");


GameWindow::GameWindow():
	d_lastFrameTime(GetTickCount()),
	d_fps_lastTime(d_lastFrameTime),
	d_fps_frames(0),
	d_fps_values(0)
{

}

GameWindow::~GameWindow()
{

}


void GameWindow::run()
{
	gameInit();
	while(d_isRunning)
	{
		MSG msg;
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message==WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		gameRun();
	}
	gameEnd();
}

void GameWindow::gameInit()
{
	d_window = createWindow(800, 600);
	setResourceGroup();
}

void GameWindow::gameRun()
{
	doTimeUpdate();
	render();
}

void GameWindow::gameEnd()
{

}

void GameWindow::render()
{

}

void GameWindow::setResourceGroup()
{
	//CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	//const char *dataPathPrefix = getDataPathPrefix();
	//char resourcePath[PATH_MAX];

	//sprintf(resourcePath, "%s%s", dataPathPrefix, "schemes/");
	//rp->setResourceGroupDirectory("schemes", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "imagesets/");
	//rp->setResourceGroupDirectory("imagesets", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "fonts/");
	//rp->setResourceGroupDirectory("fonts", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "layouts/");
	//rp->setResourceGroupDirectory("layouts", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "looknfeels/");
	//rp->setResourceGroupDirectory("looknfeels", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "lua_scripts/");
	//rp->setResourceGroupDirectory("lua_scripts", resourcePath);
	//sprintf(resourcePath, "%s%s", dataPathPrefix, "xml_schemas/");
	//rp->setResourceGroupDirectory("xml_schemas", resourcePath);

	//CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	//CEGUI::Font::setDefaultResourceGroup("fonts");
	//CEGUI::Scheme::setDefaultResourceGroup("schemes");
	//CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	//CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	//CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	//CEGUI::AnimationManager::setDefaultResourceGroup("animations");

	//CEGUI::XMLParser *parser = CEGUI::System::getSingleton().getXMLParser();
	//if(parser->isPropertyPresent("SchemaDefaultResourceGroup"))
	//{
	//	parser->setProperty("SchemeDefaultResourceGroup", "schemas");
	//}
}

void GameWindow::doTimeUpdate()
{
	//CEGUI::System &guiSystem = CEGUI::System::getSingleton();
	DWORD thisTime = GetTickCount();
	float elapsed = static_cast<float>(thisTime-d_lastFrameTime);
	d_lastFrameTime = thisTime;
	++d_fps_frames;
	if(thisTime-d_fps_lastTime>=1000)
	{
		sprintf(d_fps_textbuff, "FPS: %d", d_fps_frames);
		cout<<d_fps_textbuff<<endl;
		d_fps_values = d_fps_frames;
		d_fps_frames = 0;
		d_fps_lastTime = thisTime;
	}
	//guiSystem.injectTimePulse(elapsed/1000.0f);
}

HWND GameWindow::createWindow(int width, int height)
{
	WNDCLASS wndClass;

	wndClass.style			= 0;
	wndClass.lpfnWndProc	= wndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= GetModuleHandle(0);
	wndClass.hIcon			= LoadIcon(0, IDI_WINLOGO);
	wndClass.hCursor		= LoadCursor(0, IDC_ARROW);
	wndClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName	= 0;
	wndClass.lpszClassName	= APPLICATION_NAME;

	HWND window = 0;
	if(RegisterClass(&wndClass))
	{
		RECT wnd_size = {0, 0, width, height};
		AdjustWindowRect(&wnd_size, WS_OVERLAPPEDWINDOW, FALSE);

		window = CreateWindow(APPLICATION_NAME, APPLICATION_NAME,
			WS_OVERLAPPEDWINDOW,
			0, 0,
			wnd_size.right-wnd_size.left,
			wnd_size.bottom-wnd_size.top,
			0, 0, GetModuleHandle(0), 0);
	}else
	{
		cout<<"RegisterClass ERROR!!!"<<endl;
	}
	ShowWindow(window, SW_NORMAL);
	UpdateWindow(window);
	return window;
}

LRESULT CALLBACK GameWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CHAR:
		//CEGUI::System::getSingleton().injectChar((CEGUI::utf32)wParam);
		break;
	case WM_MOUSELEAVE:
		//mouseLeaves();
	case WM_MOUSEMOVE:
		//mouseEnters();
		//CEGUI::System::getSingleton().injectMousePosition((float)(LOWORD(lParam), (float)(HIWORD(lParam))));
		break;
	case WM_LBUTTONDOWN:
		//CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
		break;
	case WM_LBUTTONUP:
		//CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
		break;
	case WM_RBUTTONDOWN:
		//CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
		break;
	case WM_RBUTTONUP:
		//CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
		break;
	case WM_MBUTTONDOWN:
		//CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
		break;
	case WM_MBUTTONUP:
		//CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
		break;
	case 0x020A: //WM_MOUSEWHEEL
		//CEGUI::System::getSingleton().injectMouseWheelChange(static_cast<float>((short)HIWORD(wParam))/static_cast<float>(120));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		//{
		//	CEGUI::System *cegui_system = CEGUI::System::getSingletonPtr();
		//	if((cegui_system!=0) && (wParam!=SIZE_MINIMIZED))
		//	{
		//		CEGUI::Renderer *renderer = cegui_system->getRenderer();
		//		CEGUI::String id(renderer->getIdentifierString());
		//		if(id.find("Official Direct3D 9")!=id.npos)
		//		{
		//			DeviceReset_Direct3D9(hWnd, renderer);
		//		}
		//	}
		//}
		break;
	case WM_PAINT:
		{
			HDC			hDC;
			PAINTSTRUCT	ps;

			hDC = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}