#pragma once

namespace CEGUI
{

//Ϊ�˴���ʱ�����ֲ�ͬ�����������֣�FunctorCopySlot/FunctorReferenceSlot
template<typename T>
struct FunctorReferenceBinder
{
	FunctorReferenceBinder(T &functor):
		d_functor(functor){}

	T &d_functor;
};

}