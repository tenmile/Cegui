#pragma once

#include "Base.h"
#include "Vector.h"
#include "Size.h"

namespace CEGUI
{

class CEGUIEXPORT Rect
{
public:
	Rect(){}
	Rect(float left, float top, float right, float bottom);
	Rect(Point pos, Size sz);
	Point getPosition() const {return Point(d_left, d_top);}
	float getWidth() const {return d_right-d_left;}
	float getHeight() const {return d_bottom -d_top;}
	Size getSize() const {return Size(getWidth(), getHeight());}
	void setPosition(const Point &pt);
	void setWidth(float width) {d_right=d_left+width;}
	void setHeight(float height) {d_bottom=d_top+height;}
	void setSize(const Size *sze) {setWidth(sze->width);setHeight(sze->height);}
	Rect getIntersection(const Rect &rect) const;
	Rect& offset(const Point &pt);
	bool isPointInRect(const Point &pt) const;
	Rect& constrainSizeMax(const Size &sz);
	Rect& constrainSizeMin(const Size &sz);
	Rect& constrainSize(const Size &max_sz, const Size &min_sz);
	bool operator==(const Rect &rhs) const
	{
		return (d_left==rhs.d_left)&&(d_top==rhs.d_top)&&(d_right==rhs.d_right)&&(d_bottom==rhs.d_bottom);
	}
	bool operator!=(const Rect &rhs) const  {return !operator==(rhs);}
	Rect& operator=(const Rect& rhs);
	Rect operator*(float scalar) const {return Rect(d_left*scalar, d_top*scalar, d_right*scalar, d_bottom*scalar);}
	const Rect& operator*=(float scalar)
	{
		d_left *= scalar;
		d_top *= scalar;
		d_right *= scalar;
		d_bottom *= scalar;
		return *this;
	}
	Rect operator+(const Rect &r) const
	{
		return Rect(d_left+r.d_left, d_top+r.d_top, d_right+r.d_right, d_bottom+r.d_bottom);
	}

	float d_left, d_top, d_right, d_bottom;
};

}