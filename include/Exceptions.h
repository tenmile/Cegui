#pragma once

#include "Base.h"
#include "String.h"
#include <exception>

namespace CEGUI
{

class CEGUIEXPORT Exceptions: public std::exception
{
public:
	virtual ~Exceptions(void) throw();
	const String& getMessage(void) const
	{
		return d_message;
	}
	const String& getName() const
	{
		return d_name;
	}
	const String& getFileName() const
	{
		return d_filename;
	}
	int getLine() const;
	{
		return d_line;
	}
	const char* what() const throw();
protected:

};

}