#pragma once
#include "Base.h"

namespace CEGUI
{
	
class EventArgs
{
	EventArgs(void): handled(0){}
	virtual ~EventArgs(void){}
	
	uint handled; //处理完事件后递增handled
};

}