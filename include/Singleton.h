#pragma once

#include "Base.h"
#include <cassert>

namespace CEGUI
{

template<typename T>
class CEGUIEXPORT Singleton
{
protected:
	static CEGUIEXPORT T *ms_Singleton;
public:
	Singleton()
	{
		assert(!ms_Singleton);
		ms_Singleton = static_cast<T*>(this);
	}
	~Singleton()
	{
		assert(ms_Singleton);
		ms_Singleton = 0;
	}
	static T& getSingleton()
	{
		assert(ms_Singleton);
		return (*ms_Singleton);
	}
	static T* getSingletonPtr()
	{
		return ms_Singleton;
	}
private:
	Singleton &operator=(const Singleton&){return this;}
	Singleton(const Singleton&){}
};

}