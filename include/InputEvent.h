#pragma once

#include "Base.h"
#include "EventArgs.h"
#include "String.h"
#include "Vector.h"

namespace CEGUI
{

struct CEGUIEXPORT Key
{
	enum Scan
	{
		Escape			=0x01,
		One				=0x02,
		Two				=0x03,
		Three			=0x04,
		Four			=0x05,
		Five			=0x06,
		Six				=0x07,
		Seven			=0x08,
		Eight			=0x09,
		Nine			=0x0A,
		Zero			=0x0B,
		Minus			=0x0C,
		Equals			=0x0D,
		Backspace		=0x0E,
		Tab				=0x0F,
		Q				=0x10,
		W				=0x11,
		E				=0x12,
		R				=0x13,
		T				=0x14,
		Y				=0x15,
		U				=0x16,
		I				=0x17,
		O				=0x18,
		P				=0x19,
		LeftBracket		=0x1A,
		RightBracket	=0x1B,
		Return			=0x1C,
		LeftControl		=0x1D,
		A				=0x1E,
		S				=0x1F,
		D				=0x20,
		F				=0x21,
		G				=0x22,
		H				=0x23,
		J				=0x24,
		K				=0x25,
		L				=0x26,
	};
};

enum MouseButton
{
	leftButton,
	RightButton,
	MiddleButton,
	X1Button,
	X2Button,
	MouseButtonCount,
	NoButton
};

enum SystemKey
{
	LeftMouse	= 0x0001,
	RightMouse	= 0x0002,
	Shift		= 0x0004,
	Control		= 0x0008,
	MiddleMouse = 0x0010,
	X1Mouse		= 0x0020,
	X2Mouse		= 0x0040,
	Alt			= 0x0080
};

class CEGUIEXPORT WindowEventArgs: public EventArgs
{
public:
	WindowEventArgs(Window *wnd): window(wnd){}
	Window *window;
};

class CEGUIEXPORT UpdateEventArgs: public WindowEventArgs
{
public:
	UpdateEventArgs(Window *window, float tslf):
		WindowEventArgs(window),
		d_timeSinceLastFrame(tslf){}

	float d_timeSinceLastFrame;
};

class CEGUIEXPORT MouseEventArgs: public WindowEventArgs
{
public:
	MouseEventArgs(Window *wnd): WindowEventArgs(wnd){}

	Point position;
	Vector2 moveDelta;
	MouseButton button;
	uint sysKeys;
	float wheelChange;
	uint clickCount;
};

class CEGUIEXPORT MouseCursorEventArgs: public EventArgs
{
public:
	MouseCursorEventArgs(MouseCursor *cursor): mouseCursor(cursor){}

	MouseCursor *MouseCursor;
	const Image *image;
};

class CEGUIEXPORT KeyEventArgs: public WindowEventArgs
{
public:
	KeyEventArgs(Window *wnd): WindowEventArgs(wnd) {}

	utf32		codepoint;
	Key::Scan	scancode;
	uint		sysKeys;
};

class CEGUIEXPORT ActivationEventArgs: public WindowEventArgs
{
public:
	ActivationEventArgs(Window *wnd): WindowEventArgs(wnd) {}

	Window *otherWindow;
};

class CEGUIEXPORT DragDropEventArgs: public WindowEventArgs
{
public:
	DragDropEventArgs(Window* wnd): WindowEventArgs(wnd) {}

	DragContainer dragDropItem;
};

class CEGUIEXPORT ResourceEventArgs: public EventArgs
{
public:
	ResourceEventArgs(const String &type, const String &name):
		resourceType(type),
		resourceName(name){}
	String resourceType;
	String resourceName;
};

}