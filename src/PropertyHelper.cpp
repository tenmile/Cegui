#include "PropertyHelper.h"
#include "ImagesetManager.h"
#include "Imageset.h"
#include "Exceptions.h"

#include <cstdio>
#include <sstream>

namespace CEGUI
{

float PropertyHelper::stringToFloat(const String &str)
{
	using namespace std;
	float val = 0;
	sscanf(str.c_str(), " %g", &val);

	return val;
}

}