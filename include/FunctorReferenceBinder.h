#pragma once

namespace CEGUI
{

//为了传参时对两种不同的类型做区分，FunctorCopySlot/FunctorReferenceSlot
template<typename T>
struct FunctorReferenceBinder
{
	FunctorReferenceBinder(T &functor):
		d_functor(functor){}

	T &d_functor;
};

}