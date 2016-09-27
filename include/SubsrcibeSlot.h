#pragma once

#include "Base.h"
#include "FreeFunctionSlot.h"
#include "FunctorReferenceSlot.h"
#include "FunctorCopySlot.h"
#include "FunctorReferenceSlot.h"
#include "FunctorPointerSlot.h"
#include "MemberFunctionSlot.h"
#include "FunctorReferenceBinder.h"

namespace CEGUI
{

class CEGUIEXPORT SubscriberSlot
{
public:
	SubscriberSlot();
	~SubscriberSlot();
	//FreeFunctionSlot
	SubscriberSlot(FreeFunctionSlot::SlotFunction *func);
	//MemberFunctionSlot
	template<typename T>
	SubscriberSlot(bool (T::*function)(const EventArgs&), T *obj):
		d_functor_impl(new MemberFunctionSlot<T>(function, obj)){}
	//FunctorReferenceSlot,FunctorReferenceBinder做包装，以示区分
	template<typename T>
	SubscriberSlot(const FunctorReferenceBinder<T> &binder):
		d_functor_impl(new FunctorReferenceSlot<T>(binder.d_functor)){}
	//FunctorCopySlot
	template<typename T>
	SubscriberSlot(cosnt T &functor):
		d_functor_impl(new FunctorCopySlot<T>(functor)){}
	//FunctorPointerSlot
	template<typename T>
	SubscriberSlot(T *functor):
		d_functor_impl(new FunctorPointerSlot<T>(functor)){}

	bool connected()const
	{
		return d_functor_impl !=0;
	}
	void cleanup();
	bool operator()(const EventArgs &args) const
	{
		return (*d_functor_impl)(args);
	}
private:
	SlotFunctorBase *d_functor_impl;

};

}