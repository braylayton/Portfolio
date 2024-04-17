#ifndef INCLUDED_MATH_VECTOR4_H
#define INCLUDED_MATH_VECTOR4_H

#include "Vector3.h"

namespace SWGE {
namespace Math {

struct Vector4
{
		float x, y, z, w;

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float floX, float floY, float floZ, float floW) : x(floX), y(floY), z(floZ), w(floW) {}
		Vector4(Vector3 v, float inp) : x(v.x), y(v.y), z(v.z), w(inp) {}

		static Vector4 Zero()		{ return Vector4(); }
		static Vector4 One()		{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 Black()		{ return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }
		static Vector4 Gray()		{ return Vector4(0.5f, 0.5f, 0.5f, 1.0f); }
		static Vector4 DarkGray()	{ return Vector4(0.25f, 0.25f, 0.25f, 1.0f); }
		static Vector4 White()		{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 LightRed()	{ return Vector4(1.0f, 0.5f, 0.5f, 1.0f); }
		static Vector4 Red()		{ return Vector4(1.0f, 0.0f, 0.0f, 1.0f); }
		static Vector4 Green()		{ return Vector4(0.0f, 1.0f, 0.0f, 1.0f); }
		static Vector4 Blue()		{ return Vector4(0.0f, 0.0f, 1.0f, 1.0f); }
		static Vector4 Yellow()		{ return Vector4(1.0f, 1.0f, 0.0f, 1.0f); }
		static Vector4 Orange()		{ return Vector4(1.0f, 0.5f, 0.0f, 1.0f); }
		static Vector4 Cyan()		{ return Vector4(0.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 Magenta()	{ return Vector4(1.0f, 0.0f, 1.0f, 1.0f); }

		Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
		Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
		Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
		Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
		Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }

		Vector4& operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
		Vector4& operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
		Vector4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
		Vector4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
		Vector4& operator=(const Vector4& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }
};



} //SWGE
} //Math


#endif//INCLUDED_MATH_VECTOR4_H