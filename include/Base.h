#pragma once

#include "Config.h"
#include "Version.h"

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