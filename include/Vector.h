#pragma once

#include "Base.h"
#include "Size.h"

namespace CEGUI
{

class CEGUIEXPORT Vector2
{
public:
	Vector2(){};
	Vector2(float x, float y): d_x(x), d_y(y){}
	Vector2(const Vector2 &v): d_x(v.x), d_y(v.y){}
	Vector2 &operator*=(const Vector2 &vec)
	{
		d_x *= vec.d_x;
		d_y *= vec.d_y;
		return *this;
	}
	Vector2 &operator/=(const Vector2 &vec)
	{
		d_x /= vec.d_x;
		d_y /= vec.d_y;
		return *this;
	}
	Vector2 &operator+=(const Vector2 &vec)
	{
		d_x += vec.d_x;
		d_y += vec.d_y;
		return *this;
	}
	Vector2 &operator-=(const Vector2 &vec)
	{
		d_x -= vec.d_x;
		d_y -= vec.d_y;
		return *this;
	}
	Vector2 operator+(const Vector2 &vec)
	{
		return Vector2(d_x+vec.d_x, d_y+vec.d_y);
	}
	Vector2 operator-(const Vector2 &vec)
	{
		return Vector2(d_x-vec.d_x, d_y-vec.d_y);
	}
	Vector2 operator*(const Vector2 &vec)
	{
		return Vector2(d_x*vec.d_x, d_y*vec.d_y);
	}
	Vector2 operator/(const Vector2 &vec)
	{
		return Vector2(d_x/vec.d_x, d_y/vec.d_y);
	}
	bool operator==(const Vector2 &vec) const
	{
		return (d_x==vec.d_x) && (d_y==vec.d_y);
	}
	bool operator!=(const Vector2 &vec) const
	{
		return !(operator==(vec));
	}

	float d_x, d_y;
};

typedef Vector2 Point;

class CEGUIEXPORT Vector3
{
public:
	Vector3(){}
	Vector3(float x, float y, float z): d_x(x), d_y(y), d_z(z){}
	Vector3(const Vector3 &v): d_x(v.x), d_y(v.y), d_z(v.z){}

	bool operator==(const Vector3 &vec) const
	{
		return (d_x=vec.d_x)&&(d_y==vec.d_y)&&(d_z==vec.d_z);
	}
	bool operator!=(const Vector3 &vec) const
	{
		return !(operator==(vec));
	}
	Vector3 operator*(float c) const
	{
		return Vector3(d_x*c, d_y*c, d_z*c);
	}
	Vector3 operator+(const Vector3 &v) const
	{
		return Vector3(d_x+v.d_x, d_y+v.d_y, d_z+v.d_z);
	}

	float d_x, d_y, d_z;
};

}