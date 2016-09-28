#pragma once

#include "Rect.h"
#include "Vector.h"

#define cegui_absdim(x)	CEGUI::UDim(0,(x))
#define cegui_reldim(x)	CEGUI::UDim((x),0)

namespace CEGUI
{

class CEGUIEXPORT UDim
{
public:
	UDim(){}
	UDim(float scale, float offset): d_scale(scale), d_offset(offset){}
	UDim(const UDim &v): d_scale(v.d_scale), d_offset(v.d_offset){}
	~UDim(){}

	float asAbsolute(float base) const
	{
		return PixelAligned(base*d_scale) + d_offset;
	}
	float asRelative(float base) const
	{
		return (base!=0.0f)? d_offset/base+d_scale : 0.0f;
	}
	UDim operator+(const UDim &other) const
	{
		return UDim(d_scale+other.d_scale, d_offset+other.d_offset);
	}
	UDim operator-(const UDim &other) const
	{
		return UDim(d_scale-other.d_scale, d_offset-other.d_offset);
	}
	UDim operator*(const UDim &other) const
	{
		return UDim(d_scale*other.d_scale, d_offset*other.d_offset);
	}
	UDim operator/(const UDim &other) const
	{
		return UDim(other.d_scale==0.0f? 0.0f:d_scale/other.d_scale,
					other.d_offset==0.0f? 0.0f:d_offset/other.d_offset);
	}
	const UDim &operator+=(const UDim &other)
	{
		d_scale		+= other.d_scale;
		d_offset	+= other.d_offset;
		return *this;
	}
	const UDim &operator-=(const UDim &other)
	{
		d_scale		-= other.d_scale;
		d_offset	-= other.d_offset;
		return *this;
	}
	const UDim &operator*=(const UDim &other)
	{
		d_scale		*= other.d_scale;
		d_offset	*= other.d_offset;
		return *this;
	}
	const UDim &operator/=(const UDim &other)
	{
		d_scale		= (other.d_scale==0.0f? 0.0f: d_scale/other.d_scale);
		d_offset	= (other.d_offset==0.0f? 0.0f: d_offset/other.d_offset);
		return *this;
	}
	bool operator==(const UDim &other) const
	{
		return d_scale==other.d_scale && d_offset==other.d_offset;
	}
	bool operator!=(const UDim &other) const
	{
		return !operator==(other);
	}

	float d_scale, d_offset;
};

class CEGUIEXPORT UVector2
{
public:
	UVector2(){}
private:
	UDim d_x, d_y;
};

class CEGUIEXPORT URect
{
public:
	URect(){}
private:
	UVector2 d_min, d_max;
};

class CEGUIEXPORT UBox
{
public:
	UBox(): d_top(), d_left(), d_bottom(), d_right(){}
private:
	UDim d_top, d_left, d_bottom, d_right;
};

}