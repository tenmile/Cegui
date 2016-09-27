#pragma once

#include "Base.h"

namespace CEGUI
{

template<class T>
class ConstBaseIterator
{
public:
	typedef typename T::mapped_type mapped_type;

	ConstBaseIterator(typename T::const_iterator start_iter, typename T::const_iterator end_iter):
		d_currIter(start_iter),
		d_startIter(start_iter),
		d_endIter(end_iter){}
	~ConstBaseIterator(void){}
	ConstBaseIterator(const ConstBaseIterator<T> &org):
		d_currIter(org.d_currIter),
		d_startIter(org.d_startIter),
		d_endIter(org.d_endIter){}
	ConstBaseIterator<T>& operator=(const ConstBaseIterator<T> &rhs)
	{
		d_currIter = rhs.d_currIter;
		d_startIter = rhs.d_startIter;
		d_endIter = rhs.d_endIter;

		return *this;
	}

	typename T::key_type getCurrentKey(void) const
	{
		return d_currIter->first;
	}

	mapped_type getCurrentValue(void) const
	{
		return d_currIter->second;
	}

	bool isAtEnd(void) const
	{
		return d_currIter == d_endIter;
	}

	bool isAtStart(void) const
	{
		return d_currIter == d_startIter;
	}

	ConstBaseIterator<T>& operator++()
	{
		if (d_currIter != d_endIter)
		{
			++d_currIter;
		}
		return *this;
	}

	ConstBaseIterator<T> operator++(int)
	{
		ConstBaseIterator<T> tmp = *this;
		++*this;
		return tmp;
	}

	ConstBaseIterator<T>& operator--()
	{
		if (d_currIter != d_startIter)
		{
			--d_currIter;
		}
		return *this;
	}

	ConstBaseIterator<T> operator--(int)
	{
		ConstBaseIterator<T> tmp = *this;
		--*this;
		return tmp;
	}

	bool operator==(const ConstBaseIterator<T> &rhs) cosnt
	{
		return d_currIter == rhs.d_currIter;
	}

	bool operator!=(const ConstBaseIterator<T> &rhs) const
	{
		return !operator==(rhs);
	}

	mapped_type operator*() const
	{
		return d_currIter->second;
	}

	void toStart(void)
	{
		d_currIter = d_startIter;
	}

	void toEnd(void)
	{
		d_currIter = d_endIter;
	}
private:
	ConstBaseIterator(void){}
	typename T::const_iterator d_currIter;
	typename T::const_iterator d_startIter;
	typename T::const_iterator d_endIter;
};

}