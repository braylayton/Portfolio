#ifndef INCLUDED_MATH_H
#define INCLUDED_MATH_H

#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"

namespace SWGE {
namespace Math {

inline Matrix4 Transpose(const Matrix4& m)
{
	return Matrix4
	(
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	);
}

//----------------------------------------------------------------------------------------------------

struct LineSegment
{
	Vector2 from;
	Vector2 to;

	LineSegment() : from(0.0f, 0.0f), to(0.0f, 0.0f) {}
	LineSegment(float x0, float y0, float x1, float y1) : from(x0, y0), to(x1, y1) {}
	LineSegment(const Vector2& v0, const Vector2& v1) : from(v0), to(v1) {}
};

//----------------------------------------------------------------------------------------------------

struct Rect
{
	float left, top, right, bottom;

	Rect() : left(0.0f), top(0.0f), right(1.0f), bottom(1.0f) {}
	Rect(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) {}
};

//----------------------------------------------------------------------------------------------------

struct Circle
{
	Math::Vector2 center;
	float radius;

	Circle() : center(0.0f, 0.0f), radius(1.0f) {}
	Circle(const Math::Vector2& center, float radius) : center(center), radius(radius) {}
	Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
};

//----------------------------------------------------------------------------------------------------

struct AABB
{
	Vector3 center;
	Vector3 extend;

	AABB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f) {}
	AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}
};

//----------------------------------------------------------------------------------------------------

struct OBB
{
	Vector3 center;
	Vector3 extend;
	Quaternion orientation;

	OBB()
		: center(0.0f, 0.0f, 0.0f)
		, extend(1.0f, 1.0f, 1.0f)
		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(float x, float y, float z, float sx, float sy, float sz)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(float x, float y, float z, float sx, float sy, float sz, const Quaternion& orientation)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, orientation(orientation)
	{}

	OBB(const Vector3& center, const Vector3& extend, const Quaternion& orientation)
		: center(center)
		, extend(extend)
		, orientation(orientation)
	{}
};

//----------------------------------------------------------------------------------------------------

struct Sphere
{
	Vector3 center;
	float radius;

	Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f) {}
	Sphere(float x, float y, float z, float radius) : center(x, y, z), radius(radius) {}
	Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
};

//----------------------------------------------------------------------------------------------------

struct Ray
{
	Vector3 org;
	Vector3 dir;

	Ray() : org(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, 1.0f) {}
	Ray(float x, float y, float z, float dx, float dy, float dz) : org(x, y, z), dir(dx, dy, dz) {}
	Ray(const Vector3& org, const Vector3& dir) : org(org), dir(dir) {}
};

//----------------------------------------------------------------------------------------------------

struct Plane
{
	Vector3 n;
	float d;

	Plane() : n(0.0f, 1.0f, 0.0f), d(0.0f) {}
	Plane(float a, float b, float c, float d) : n(a, b, c), d(d) {}
};

//----------------------------------------------------------------------------------------------------
const float kPi = 3.14159265358979f;
const float kTwoPi = 6.28318530717958f;
const float kPiByTwo = 1.57079632679489f;
const float kRootTwo = 1.41421356237309f;
const float kRootThree = 1.73205080756887f;
const float kDegToRad = kPi / 180.0f;
const float kRadToDeg = 180.0f / kPi;

//----------------------------------------------------------------------------------------------------

template <typename T> inline T Min(T a, T b)				{ return (a > b) ? b : a; }
template <typename T> inline T Max(T a, T b)				{ return (a < b) ? b : a; }
template <typename T> inline T Clamp(T value, T min, T max) { return Max(min, Min(max, value)); }

inline float Abs(float value)	{ return (value >= 0.0f) ? value : -value; }
inline float Sign(float value)	{ return (value >= 0.0f) ? 1.0f : -1.0f; }
inline float Sqr(float value)	{ return value * value; }
inline float Sqrt(float value)	{ return sqrtf(value); }

inline bool Compare(float a, float b, float epsilon = FLT_MIN) { return Abs(a - b) <= epsilon; }

inline bool IsZero(float value)			{ return Compare(value, 0.0f); }
inline bool IsZero(const Vector2& v)	{ return IsZero(v.x) && IsZero(v.y); }
inline bool IsZero(const Vector3& v)	{ return IsZero(v.x) && IsZero(v.y) && IsZero(v.z); }

inline Vector2 PerpendicularLH(const Vector2& v) { return Vector2(-v.y, v.x); }
inline Vector2 PerpendicularRH(const Vector2& v) { return Vector2(v.y, -v.x); }

inline float MagnitudeSqr(const Vector2& v)		{ return (v.x * v.x) + (v.y * v.y); }
inline float MagnitudeSqr(const Vector3& v)		{ return (v.x * v.x) + (v.y * v.y) + (v.z * v.z); }
inline float Magnitude(const Vector2& v)		{ return Sqrt(MagnitudeSqr(v)); }
inline float Magnitude(const Vector3& v)		{ return Sqrt(MagnitudeSqr(v)); }
inline float MagnitudeXZSqr(const Vector3& v)	{ return (v.x * v.x) + (v.z * v.z); }
inline float MagnitudeXZ(const Vector3& v)		{ return Sqrt(MagnitudeXZSqr(v)); }
inline float Magnitude(const Quaternion& q)		{ return Sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)); }

inline Vector2 Normalize(const Vector2& v)		{ return v / Magnitude(v); }
inline Vector3 Normalize(const Vector3& v)		{ return v / Magnitude(v); }
inline Quaternion Normalize(const Quaternion& q){ return q / Magnitude(q); }

inline float DistanceSqr(const Vector2& a, const Vector2& b)	{ return MagnitudeSqr(a - b); }
inline float DistanceSqr(const Vector3& a, const Vector3& b)	{ return MagnitudeSqr(a - b); }
inline float Distance(const Vector2& a, const Vector2& b)		{ return Sqrt(DistanceSqr(a, b)); }
inline float Distance(const Vector3& a, const Vector3& b)		{ return Sqrt(DistanceSqr(a, b)); }
inline float DistanceXZSqr(const Vector3& a, const Vector3& b)	{ return MagnitudeXZSqr(a - b); }
inline float DistanceXZ(const Vector3& a, const Vector3& b)		{ return Sqrt(DistanceXZSqr(a, b)); }
inline float Dot(const Vector2& a, const Vector2& b)			{ return (a.x * b.x) + (a.y * b.y); }
inline float Dot(const Vector3& a, const Vector3& b)			{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
//inline Vector2 Project(const Vector2& v, const Vector2& n) { return n * (Dot(v, n) / Dot(n, n)); }//
inline Vector3 Project(const Vector3& v, const Vector3& n)		{ return n * (Dot(v, n) / Dot(n, n)); }
//inline Vector2 Reflect(const Vector2& v, const Vector2& normal) { return v - (normal * Dot(v, normal) * 2.0f); }
inline Vector3 Reflect(const Vector3& v, const Vector3& normal) { return v - (normal * Dot(v, normal) * 2.0f); }

inline Vector3 GetTranslation(const Matrix4& m)		{ return Vector3(m._41, m._42, m._43); }
inline Vector3 GetRight(const Matrix4& m)			{ return Vector3(m._11, m._12, m._13); }
inline Vector3 GetUp(const Matrix4& m)				{ return Vector3(m._21, m._22, m._23); }
inline Vector3 GetForward(const Matrix4& m)			{ return Vector3(m._31, m._32, m._33); }

inline Vector3 GetPoint(const Ray& ray, float distance) { return ray.org + (ray.dir * distance); }

inline Vector2 Lerp(const Vector2& v0, const Vector2& v1, float t)	{ return v0 + ((v1 - v0) * t); }
inline Vector3 Lerp(const Vector3& v0, const Vector3& v1, float t)	{ return v0 + ((v1 - v0) * t); }
inline Quaternion Lerp(Quaternion q0, Quaternion q1, float t)		{ return q0 * (1.0f - t) + (q1 * t); }



inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
	ASSERT(Abs(Dot(Normalize(a), Normalize(b))) < 1.0f, "[Math] Cannot cross two vectors that are parallel.");
	return Vector3
	(
		(a.y * b.z) - (a.z * b.y), 
		(a.z * b.x) - (a.x * b.z), 
		(a.x * b.y) - (a.y * b.x)
	);
}

inline Vector2 Rotate(const Vector2& v, float rad)
{
	const float kCosAngle = cos(rad);
	const float kSinAngle = sin(rad);
	return Vector2
	(
		v.x * kCosAngle - v.y * kSinAngle,
		v.y * kCosAngle + v.x * kSinAngle
	);
}

inline float Determinant(const Matrix4& m)
{
	float det = 0.0f;
	det = (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}

inline Matrix4 Adjoint(const Matrix4& m)
{
	return Matrix4
	(
		(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	);
}

inline Matrix4 Inverse(const Matrix4& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}

inline Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
{
	return Vector3
	(
		v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41,
		v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42,
		v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43
	);
}

inline Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
{
	return Vector3
	(
		v.x * m._11 + v.y * m._21 + v.z * m._31,
		v.x * m._12 + v.y * m._22 + v.z * m._32,
		v.x * m._13 + v.y * m._23 + v.z * m._33
	);
}

inline Matrix4 QuaternionToMatrix4(const Quaternion q1)
{
	Quaternion q = Normalize(q1);
	return Matrix4(
		1-2 * (q.y * q.y) - 2 * (q.z * q.z),	2 * q.x*q.y - 2 * q.z*q.w,				2 * q.x*q.z + 2 * q.y*q.w,				0,
		2 * q.x*q.y + 2 * q.z*q.w,				1 - 2 * (q.x * q.x) - 2 * (q.z * q.z),	2 * q.y*q.z - 2 * q.x*q.w,				0,
		2 * q.x*q.z - 2 * q.y*q.w,				2 * q.y*q.z + 2 * q.x*q.w,				1 - 2 * (q.x * q.x) - 2 * (q.y * q.y),	0,
		0,											0,											0,											1);

}

inline Quaternion Matrix4ToQuaternion(const Matrix4 M)
{
	Quaternion T;
	T.w = (Sqrt(1 + M._11 + M._22 + M._33)) * 0.5f;
	float W = T.w * 4;
	W = 1 / W;
	T.x = (M._32 - M._23) * W;
	T.y = (M._13 - M._31) * W;
	T.z = (M._21 - M._12) * W;
	return T;
}

Quaternion QuaternionRotationAxis(const Vector3& axis, float rad);
Quaternion QuaternionLookRotation(const Vector3& Look, const Vector3& up);
Quaternion QuaternionFromToRotation(const Vector3& From, const Vector3& To);
Quaternion Slerp(Quaternion q0, Quaternion q1, float t);
Matrix4 MatrixRotationAxis(const Vector3& axis, float rad);


bool PointInRect(const Vector2& point, const Rect& rect);
bool PointInCircle(const Vector2& point, const Circle& circle);

bool Intersect(const LineSegment& a, const LineSegment& b);
bool Intersect(const Circle& c0, const Circle& c1);
bool Intersect(const Rect& r0, const Rect& r1);

bool Intersect(const LineSegment& l, const Circle& c);
bool Intersect(const Circle& c, const LineSegment& l);

bool Intersect(const Circle& c, const Rect& r);
bool Intersect(const Rect& r, const Circle& c);

bool Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance); // Ray Triangle(a,b,c) intersect  
bool Intersect(const Ray& ray, const Plane& plane, float& distance);
bool Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit);
bool Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit);
bool Intersect(const Vector3& point, const AABB& aabb);
bool Intersect(const Vector3& point, const OBB& obb);

}
}
#endif // !INCLUDED_MATH_H
