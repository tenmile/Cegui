#pragma once

#include "Base.h"
#include <string.h>
#include <stdexcept>
#include <cstddef>
#include <algorithm>

namespace CEGUI
{

#define STR_QUICKBUFF_SIZE 32

typedef uint8 utf8;
typedef uint32 utf32;

class CEGUIEXPORT String
{
public:
	typedef utf32			value_type;			//code point类型
	typedef size_t			size_type;
	typedef std::ptrdiff_t	difference_type;
	typedef utf32&			reference;
	typedef const utf32&	const_reference;
	typedef utf32*			pointer;
	typedef const utf32*	const_pointer;

	static const size_type	npos;  //注意是static类型
private:
	size_type	d_cplength;			//code point长度
	size_type	d_reverve;			//???

	utf32		d_quickbuff[STR_QUICKBUFF_SIZE];	//buffer for smallish strings
	utf32*		d_buffer;							//pointer to the main buffer memory,和quickbuff二选一
public:
	class iterator : public std::iterator<std::random_access_iterator_tag, utf32>
	{
	public:
		iterator(): d_ptr(0){}
		explicit iterator(utf32* const ptr): d_ptr(ptr){}

		utf32& operator*() const
		{
			return *d_ptr;
		}
		utf32* operator->() const
		{
			return &**this;
		}
		String::iterator& operator++()
		{
			++d_ptr;
			return *this;
		}
		String::iterator operator++(int)
		{
			String::iterator temp = *this;
			++*this;
			return temp;
		}
		String::iterator& operator--()
		{
			--d_ptr;
			return *this;
		}
		String::iterator operator--(int)
		{
			String::iterator temp = *this;
			--*this;
			return temp;
		}
		String::iterator& operator+=(difference_type offset)
		{
			d_ptr += offset;
			return *this;
		}
		String::iterator operator+(difference_type offset) const
		{
			String::iterator temp = *this;
			return temp += offset;
		}
		String::iterator& operator-=(difference_type offset)
		{
			return *this += -offset;
		}
		String::iterator operator-(difference_type offset) const
		{
			String::iterator temp = *this;
			return temp -= offset;
		}
		utf32& operator[](difference_type offset) const
		{
			return *(*this + offset);
		}
		String::iterator& operator=(const String::iterator& iter)
		{
			d_ptr = iter.d_ptr;
			return *this;
		}
		friend difference_type operator-(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr - rhs.d_ptr;
		}
		friend String::iterator operator+(difference_type offset, const String::iterator &iter)
		{
			return iter + offset;
		}
		friend bool operator==(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr == rhs.d_ptr;
		}
		friend bool operator!=(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr != rhs.d_ptr;
		}
		friend bool operator<(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr < rhs.d_ptr;
		}
		friend bool operator>(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr > rhs.d_ptr;
		}
		friend bool operator<=(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr <= rhs.d_ptr;
		}
		friend bool operator>=(const String::iterator &lhs, const String::iterator &rhs)
		{
			return lhs.d_ptr >= rhs.d_ptr;
		}

		utf32 *d_ptr;
	};

	class const_iterator : public std::iterator<std::random_access_iterator_tag, const utf32>
	{
	public:
		const_iterator() : d_ptr(0) {}
		explicit const_iterator(const utf32* const ptr) : d_ptr(ptr) {}

		const utf32& operator*() const
		{
			return *d_ptr;
		}
		const utf32* operator->() const
		{
			return &**this;
		}
		String::const_iterator& operator++()
		{
			++d_ptr;
			return *this;
		}
		String::const_iterator operator++(int)
		{
			String::const_iterator temp = *this;
			++*this;
			return temp;
		}
		String::const_iterator& operator--()
		{
			--d_ptr;
			return *this;
		}
		String::const_iterator operator--(int)
		{
			String::const_iterator temp = *this;
			--*this;
			return temp;
		}
		String::const_iterator& operator+=(difference_type offset)
		{
			d_ptr += offset;
			return *this;
		}
		String::const_iterator operator+(difference_type offset) const
		{
			String::const_iterator temp = *this;
			return temp += offset;
		}
		String::const_iterator& operator-=(difference_type offset)
		{
			return *this += -offset;
		}
		String::const_iterator operator-(difference_type offset) const
		{
			String::const_iterator temp = *this;
			return temp -= offset;
		}
		utf32& operator[](difference_type offset) const
		{
			return *(*this + offset);
		}
		String::const_iterator& operator=(const String::iterator& iter)
		{
			d_ptr = iter.d_ptr;
			return *this;
		}
		friend difference_type operator-(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr - rhs.d_ptr;
		}
		friend String::const_iterator operator+(difference_type offset, const String::const_iterator &iter)
		{
			return iter + offset;
		}
		friend bool operator==(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr == rhs.d_ptr;
		}
		friend bool operator!=(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr != rhs.d_ptr;
		}
		friend bool operator<(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr < rhs.d_ptr;
		}
		friend bool operator>(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr > rhs.d_ptr;
		}
		friend bool operator<=(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr <= rhs.d_ptr;
		}
		friend bool operator>=(const String::const_iterator &lhs, const String::const_iterator &rhs)
		{
			return lhs.d_ptr >= rhs.d_ptr;
		}

		const utf32 *d_ptr;
	};
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
public:
	//比默认的快，但std::map中不再按字母排序
	struct FastLessCompare
	{
		bool operator()(const String &a, const String &b) const
		{
			const size_t la = a.length();
			const size_t lb = b.length();
			if (la == lb)
			{
				return memcmp(a.ptr(), b.ptr(), la*sizeof(utf32))<0;
			}
			return (la < lb);
		}
	};
public:
	String()
	{
		init();
	}
	~String();
	String(const String &str)
	{
		init();
		assign(str);
	}
	String(const String &str, size_type str_idx, size_type str_num = npos)
	{
		init();
		assign(str, str_idx, str_num);
	}
	String(const std::string &std_str)
	{
		init();
		assign(std_str);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	String(const std::string &std_str, size_type str_idx, size_type str_num = npos)
	{
		init();
		assign(std_str, str_idx, str_num);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	String(const utf8 *utf8_str)
	{
		init();
		assign(utf8_str);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	String(const utf *utf8_str, size_type chars_len)
	{
		init();
		assign(utf8_str, chars_len);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	//将一个字符重复多次
	String(size_type num, utf32 code_point)
	{
		init();
		assign(num, code_point);
	}
	String(const_iterator iter_beg, const_iterator iter_end)
	{
		init();
		append(iter_beg, iter_end);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	//以0结尾的字符串
	String(const char *cstr)
	{
		init();
		assign(cstr);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	//字符数组
	String(const char *chars, size_type chars_len)
	{
		init();
		assign(chars, chars_len);
	}
	size_type size() const
	{
		return d_cplength;
	}
	size_type length() const
	{
		return d_cplength;
	}
	bool empty() const
	{
		return d_cplength == 0;
	}
	//只要比这个数大就会抛出异常std::length_error exception,注意是static
	static size_type max_size()
	{
		return (size_type)-1 / sizeof(utf32);
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	size_type capacity() const
	{
		return d_reverve - 1;
	}
	//exception std::length_error Thrown if resulting String object would be too big.
	//num等于0，调整为当前字符串一样大小
	//num小于当前reserve，缩小为num和字符串大小的最大值
	//num大于当前reserve，扩大
	void reserve(size_type num = 0)
	{
		if (num == 0)
		{
			trim();
		}
		else
		{
			grow(num);
		}
	}

	int compare(const String &str) const
	{
		return compare(0, d_cplength, str);
	}

	int compare(size_type idx, size_type len, const String &str, size_type str_idx=0, size_type str_len=npos) const
	{
		if ((d_cplength<idx) || (str.d_cplength<str_idx))
		{
			CEGUI_THROW(std::out_of_range("Index is out of range for CEGUI::String"));
		}
		if ((len == npos) ||(idx+len>d_cplength))
		{
			len = d_cplength-idx;
		}
		if ((str_len==npos) || (str_idx+str_len>str.d_cplength))
		{
			str_len = str.d_cplength - str_idx;
		}

		int val = (len==0) ? 0 : utf32_comp_utf32(&ptr()[idx], &str.ptr()[str_idx], (len<str_len)?len:str_len);
		return (val!=0) ? ((val<0)?-1:1) : (len<str_len)?-1:(len==str_len)?0:1;
	}

	int compare(const std::string &std_str) const
	{
		return compare(0, d_cplength, std_str);
	}

};

}