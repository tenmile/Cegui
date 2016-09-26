#pragma once

#define CEGUIEXPORT __declspec(dllexport)

#include "Config.h"
#include "Version.h"
#include <string>
#include <algorithm>

#define ceguimin std::min
#define ceguimax std::max

#define CEGUI_TRY try
#define CEGUI_CATCH(e) catch(e)
#define CEGUI_THROW(e) throw(e)
#define CEGUI_RETHOW throw

namespace
{

	typedef unsigned long ulong;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned char uchar;

	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	
	//Default native horizontal resolution(for fonts and imagesets)
	static const float DefaultNativeHorzRes = 640.0f;
	//Default native vertical resolution(for font and imagesets)
	static const float DefaultNativeVertRes = 480.0f;

	typedef std::ostream OutStream;

}