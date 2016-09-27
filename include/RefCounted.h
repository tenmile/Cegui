#pragma once

namespace CEGUI
{

template<typename T>
class RefCounted
{
public:
	RefCounted():
		d_object(0),
		d_count(0){}
	RefCounted(T *obj):
		d_object(obj),
		d_count((obj!=0)?new unsigned int(1):0){}
	RefCounted(const RefCounted<T> &other):
		d_object(other.d_object),
		d_count(other.d_count)
	{
		if (d_count)
		{
			addRef();
		}
	}
	~RefCounted()
	{
		if (d_object)
		{
			release();
		}
	}
	RefCounted<T>& operator=(const RefCounted<T> &other)
	{
		if (*this!=other)
		{
			if (d_object)
			{
				release();
			}
			d_object = other.d_object;
			d_count = d_object? other.d_count : 0;
			if (d_count)
			{
				addRef();
			}
		}
		return *this;
	}
	bool operator==(const RefCounted<T> &other) const
	{
		return d_object == other.d_object;
	}
	bool operator!=(const RefCounted<T> &other) const
	{
		return d_object != other.d_object;
	}
	const T& operator*() const
	{
		return *d_object;
	}
	T& operator()
	{
		return *d_object;
	}
	const T* operator->() const
	{
		return d_object;
	}
	T* operator->()
	{
		return d_object;
	}
	bool isValid() const
	{
		return d_object != 0;
	}
private:
	void addRef()
	{
		++*d_count;
	}
	void release()
	{
		if (!--*d_count)
		{
			delete d_object;
			delete d_count;
			d_object = 0;
			d_count = 0;
		}
	}
	T *d_object;
	unsigned int *d_count;
};

}