#pragma once

#include <windows.h>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	virtual void gameInit();
	virtual void gameEnd();
	virtual void gameRun();
	void run();

	void doTimeUpdate();

	HWND createWindow(int width, int height);
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void render();
	void setResourceGroup();

	static const TCHAR APPLICATION_NAME[];
protected:
	bool d_isRunning;
	DWORD d_lastFrameTime;
	DWORD d_fps_lastTime;
	int d_fps_frames;
	int d_fps_values;
	char d_fps_textbuff[16];

	HWND d_window;
};