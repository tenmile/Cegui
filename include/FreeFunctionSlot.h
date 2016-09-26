#pragma once
#include "SlotFunctorBase"

namespace
{

class FreeFunctionSlot: public SlotFunctorBase
{
public:
	typedef bool(SlotFunction)(const EventArgs&);
	FreeFunctionSlot(SlotFunction *func):
		d_function(func){}
	virtual bool operator()(const EventArgs &args)
	{
		return d_function(args);
	}
private:
	SlotFunction *d_function;
};

}