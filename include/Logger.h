#pragma once

#include "Base.h"
#include "String.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include "Singleton.h"

namespace CEGUI
{

enum LoggingLevel    //越往下越不重要，信息会越来愈多
{
	Errors,
	Warnings,
	Standard,
	Informative,
	Insane
};

class CEGUIEXPORT Logger: public Singleton<Logger>
{
public:
	Logger();
	~Logger();
	void setLoggingLevel(LoggingLevel level)
	{
		d_level = level;
	}
	LoggingLevel getLoggingLevel() const
	{
		return d_level;
	}
	virtual void logEvent(const String &message, LoggingLevel level=Standard)=0;
	virtual void setLogFilename(const String& filename, bool append = false)=0;
protected:
	LoggingLevel d_level;
private:
	Logger(const Logger&): Singleton<Logger>(){}
	Logger& operator=(const Logger&)
	{
		return *this;
	}
};

}