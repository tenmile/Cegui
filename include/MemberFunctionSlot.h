#pragma once

#include "SlotFunctorBase.h"

namespace CEGUI
{

template<typename T>
class MemberFunctionSlot: public SlotFunctorBase
{
public:
	//��������˳�Աָ����÷�
	typedef bool(T::*MemberFunctionType)(const EventArgs&);

	MemberFunctionSlot(MemberFunctionType func, T *obj):
		d_function(func),
		d_object(obj){}
	virtual bool operator()()(const EventArgs& args)
	{
		return (d_object->*d_function)(args);
	}
private:
	MemberFunctionType d_function;
	T *d_object;
};

}