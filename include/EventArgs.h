#ifndef _EventArgs_h_
#define _EventArgs_h_
namespace
{
	
class EventArgs
{
	EventArgs(void): handled(0){}
	virtual ~EventArgs(void){}
	
	uint handled; //处理完事件后递增handled
}

}
#endif