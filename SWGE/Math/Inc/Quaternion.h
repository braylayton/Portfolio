#ifndef INCLUDED_MATH_QUATERNION_H
#define INCLUDED_MATH_QUATERNION_H

namespace SWGE {
namespace Math {

struct Quaternion
{
	float x, y, z, w;

	Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	//static Quaternion Quaternion::Zero()		{ return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); }
	//static Quaternion Quaternion::Identity()	{ return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }
	//static Quaternion Quaternion::Conjugate(const Quaternion&) { Quaternion Q; Q.x = -Q.x; Q.y = -Q.y; Q.z = -Q.z; Normalize(Q.w); }
	

	Quaternion operator+(const Quaternion& rhs) const	{ return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	Quaternion operator-(const Quaternion& rhs) const	{ return Quaternion(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
	Quaternion operator*(float s) const					{ return Quaternion(x * s, y * s, z * s, w * s); }
	Quaternion operator/(float s) const					{ VERIFY(s != 0, "[Math::Quaternion /] Cannot divide by zero!"); return Quaternion(x / s, y / s, z / s, w / s); }

	Quaternion operator*(const Quaternion& rhs)
	{
		return Quaternion{ (x * rhs.w) + (w*rhs.x) + (y * rhs.z) - (z * rhs.y),
						   (y * rhs.w) + (w*rhs.y) + (z * rhs.x) - (x * rhs.z),
						   (z * rhs.w) + (w*rhs.z) + (x * rhs.y) - (y * rhs.x),
						   (w * rhs.w) - (x*rhs.x) - (y * rhs.y) - (z * rhs.z) };
	}

	Quaternion& operator+=(const Quaternion& rhs)	{ x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
	Quaternion& operator-=(const Quaternion& rhs)	{ x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
	Quaternion& operator*=(float s)					{ x *= s; y *= s; z *= s; w *= s; return *this; }
	Quaternion& operator/=(float s)					{ VERIFY(s != 0, "[Math::Quaternion /=] Cannot divide by zero!"); x /= s; y /= s; z /= s; w /= s; return *this; }

};

} // Math
} // SWGE
#endif // !INCLUDED_MATH_QUATERNION_H
