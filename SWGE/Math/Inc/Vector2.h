#ifndef INCLUDED_MATH_VECTOR2_H
#define INCLUDED_MATH_VECTOR2_H

namespace SWGE {
namespace Math {

struct Vector2
{
	float x, y;
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float floX, float floY)
		: x(floX)
		, y(floY)
	{}
	//Useful Equations
	static Vector2 Zero()	{ return Vector2(); }
	static Vector2 One()	{ return Vector2(1.0f, 1.0f); }
	static Vector2 XAxis()	{ return Vector2(1.0f, 0.0f); }
	static Vector2 YAxis()	{ return Vector2(0.0f, 1.0f); }

	inline Vector2 operator-()
	{
		return{ -x, -y};
	}

	// Addition 
	inline Vector2 operator+(Vector2 v) const
	{
		return { x + v.x, y + v.y };
	}
	inline Vector2& operator+=(Vector2 v)
	{
		x += v.x; y += v.y; return *this;
	}
	//Subtraction
	inline Vector2 operator-(Vector2 v) const
	{
		return { x - v.x, y - v.y };
	}
	inline Vector2& operator-=(Vector2 v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	//Multiplication 
	inline Vector2 operator*(float s)
	{
		return { x * s, y * s };
	}
	inline Vector2& operator*=(float s)
	{
		x *= s; y *= s; return *this;
	}
	//Division
	inline Vector2 operator/(float s) const
	{
		VERIFY(s != 0, "[Math::Vector2 /] Can't divide by zero!");
		return { x / s, y / s };
	}
	inline Vector2& operator/= (float s)
	{
		VERIFY(s != 0, "[Math::Vector2 /=] Can't divide by zero!");
		x /= s;
		y /= s;
		return *this;
	}
};
}
}
#endif // !1