#include "Logger.h"

namespace CEGUI
{

template<> Logger* Singleton<Logger>::ms_Singleton = 0;

Logger::Logger():
	d_level(Standard){}
Logger::~Logger(){}

}