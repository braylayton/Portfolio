#include "Precompiled.h"
#include "Matrix4.h"
#include "QMath.h"

using namespace SWGE;
using namespace Math;


Vector3 Matrix4::Position()
{
	return Vector3(_41, _42, _43);
}

Vector3 Matrix4::Scale()
{
	Vector3 s;
	s.x = SWGE::Math::Magnitude(Vector3(_11, _12, _13));
	s.y = SWGE::Math::Magnitude(Vector3(_21, _22, _23));
	s.z = SWGE::Math::Magnitude(Vector3(_31, _32, _33));
	return s;
}

Quaternion Matrix4::Rotation()
{
	Vector3 s = Scale();
	Matrix4 m = *this;
	s.x = 1 / s.x;
	s.y = 1 / s.y;
	s.z = 1 / s.z;
	m._11 *= s.x; m._12 *= s.x; m._13 *= s.x;
	m._21 *= s.y; m._22 *= s.y; m._23 *= s.y;
	m._31 *= s.z; m._32 *= s.z; m._33 *= s.z;
	Quaternion q = SWGE::Math::Matrix4ToQuaternion(m);
	return q;
}