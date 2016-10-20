#include "config.h"

#include "Win32AppHelper.h"
#include "CEGUI.h"
#include <TCHAR.H>

const TCHAR Win32AppHelper::APPLICATION_NAME[] = _TEXT("Crazy Eddie's GUI Mk-2 - Sample Application");
const TCHAR Win32AppHelper::REGISTER_CLASS_ERROR[] = _TEXT("Failed to register window class.");
const TCHAR Win32AppHelper::CREATE_WINDOW_ERROR[] = _TEXT("Failed to create window.");
const TCHAR Win32AppHelper::CREATE_D3D_ERROR[] = _TEXT("Failed to create main Direct3D object.");
const TCHAR Win32AppHelper::CREATE_DEVICE_ERROR[] = _TEXT("Failed to create Direct3D Device object.");

bool Win32AppHelper::d_mouseInWindow = false;

void DeviceReset_Direct3D9(HWND window, CEGUI::Renderer *renderer);
void DeviceReset_Direct3D81(HWND window, CEGUI::Renderer *renderer);
void DeviceReset_Direct3D10(HWND window, CEGUI::Renderer *renderer);


HWND Win32AppHelper::createApplicationWindow(int width, int height)
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
		MessageBox(0, REGISTER_CLASS_ERROR, APPLICATION_NAME, MB_ICONERROR|MB_OK);
	}
	return window;
}

LRESULT CALLBACK Win32AppHelper::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void Win32AppHelper::mouseEnters()
{
	if(!d_mouseInWindow)
	{
		d_mouseInWindow = true;
		ShowCursor(false);
	}
}

void Win32AppHelper::mouseLeaves()
{
	if(!d_mouseInWindow)
	{
		d_mouseInWindow = false;
		ShowCursor(true);
	}
}

bool Win32AppHelper::initialiseDirectInput(HWND window, Wind32AppHelper::DirectInputState &dis)
{

}