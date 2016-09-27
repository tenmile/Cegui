#pragma once
#include "Base.h"

namespace CEGUI
{
	
class CEGUIEXPORT EventArgs
{
	EventArgs(void): handled(0){}
	virtual ~EventArgs(void){}
	
	uint handled; //处理完事件后递增handled
};

}