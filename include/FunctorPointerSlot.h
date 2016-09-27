#pragma once

#include "SlotFunctorBase.h"

namespace CEGUI
{

template<typename T>
class FunctorPointerSlot: public SlotFunctorBase
{
public:
	FunctorPointerSlot(T *functor):
	  d_functor(functor){}
	virtual bool operator()(const EventArgs &args)
	{
		return (*d_functor)(args);
	}
private:
	T *d_functor;
};

}