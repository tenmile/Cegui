#include "FirstWindow.h"

int main()
{
	FirstWindow app;
	return app.run();
}

while(true)
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
	}else
	{
		break;
	}
}

HWND createApplicationWindow(int width, int height)
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
		cout<<"Failed to RegisterClass!"<<endl;
	}
	return window;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CHAR:
		CEGUI::System::getSingleton().injectChar((CEGUI::utf32)wParam);
		break;
	case WM_MOUSELEAVE:
		mouseLeaves();
	case WM_MOUSEMOVE:
		mouseEnters();
		CEGUI::System::getSingleton().injectMousePosition((float)(LOWORD(lParam), (float)(HIWORD(lParam))));
		break;
	case WM_LBUTTONDOWN:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
		break;
	case WM_LBUTTONUP:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
		break;
	case WM_RBUTTONDOWN:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
		break;
	case WM_RBUTTONUP:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
		break;
	case WM_MBUTTONDOWN:
		CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
		break;
	case WM_MBUTTONUP:
		CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
		break;
	case 0x020A: //WM_MOUSEWHEEL
		CEGUI::System::getSingleton().injectMouseWheelChange(static_cast<float>((short)HIWORD(wParam))/static_cast<float>(120));
		break;
	case WM_DESTROY:
		PostAppMessage(0);
		break;
	case WM_SIZE:
		{
			CEGUI::System *cegui_system = CEGUI::System::getSingletonPtr();
			if((cegui_system!=0) && (wParam!=SIZE_MINIMIZED))
			{
				CEGUI::Renderer *renderer = cegui_system->getRenderer();
				CEGUI::String id(renderer->getIdentifierString());
				if(id.find("Official Direct3D 9")!=id.npos)
				{
					DeviceReset_Direct3D9(hWnd, renderer);
				}
			}
		}
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