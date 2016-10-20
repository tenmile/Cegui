#pragma once

#include <windows.h>
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Win32AppHelper
{
public:
	struct DirectInputState
	{
		DirectInputState(): directInput(0), keyboardDevice(0) {}
		LPDIRECTINPUT8 directInput;
		LPDIRECTINPUTDEVICE8 keyboardDevice;
	};

	static HWND createApplicationWindow(int width, int height);
	static void mouseEnters();
	static void mouseLeaves();
	static bool initialiseDirectInput(HWND window, Wind32AppHelper::DirectInputState &dis);
	static void cleanupDirectInput(Win32AppHelper::DirectInputState &dis);
	static void doDirectInputEvents(const Win32AppHelper::DirectInputState &dis);
	static bool doWin32Events(bool &idle);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT messagem, WPARAM wParam, LPARAM lParam);

	static const TCHAR APPLICATION_NAME[];
	static const TCHAR REGISTER_CLASS_ERROR[];
	static const TCHAR CREATE_WINDOW_ERROR[];
	static const TCHAR CREATE_D3D_ERROR[];
	static const TCHAR CREATE_DEVICE_ERROR[];

private:
	static bool d_mouseInWindow;
};