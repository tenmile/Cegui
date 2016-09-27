#pragma once

#define CEGUIEXPORT __declspec(dllexport)

#include "Config.h"
#include "Version.h"
#include <cassert>
#include <string>
#include <algorithm>
//Bring in forward references to all GUI base system classes
#include "ForwardRefs.h"

#define ceguimin std::min
#define ceguimax std::max

#define CEGUI_TRY try
#define CEGUI_CATCH(e) catch(e)
#define CEGUI_THROW(e) throw(e)
#define CEGUI_RETHOW throw

#define CEGUI_ALIGN_ELEMENTS_TO_PIXELS 1
#define PixelAligned(x) ((float)(int)((x)+((x)>0.0f?0.5f:-0.5f)))

namespace CEGUI
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