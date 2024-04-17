#ifndef INCLUDED_MATH_VECTOR3_H
#define INCLUDED_MATH_VECTOR3_H

namespace SWGE {
namespace Math {

struct Vector3
{
	float x, y, z;
	
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float flox, float floy, float floz)
	{
		x = flox;
		y = floy;
		z = floz;
	}
	
	//Useful Functions
	static Vector3 Zero()	{ return Vector3(); }
	static Vector3 One()	{ return Vector3(1.0f, 1.0f, 1.0f); }
	static Vector3 XAxis()	{ return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 YAxis()	{ return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 ZAxis()	{ return Vector3(0.0f, 0.0f, 1.0f); }

	inline Vector3 operator-() const
	{
		return { -x, -y, -z };
	}

	// Addition 
	inline Vector3 operator+(Vector3 v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}
	inline Vector3& operator+=(Vector3 v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	//Subtraction
	inline Vector3 operator-(Vector3 v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}
	inline Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	//Multiplication 
	inline Vector3 operator*(float s) const
	{
		return { x * s, y * s, z * s };
	}

	inline Vector3& operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	/*inline Vector3 operator*(Vector3 v) const
	{
		return { x * v.x, y * v.y, z * v.z };
	}*/
	//inline Vector3& operator*=(const Vector3 v)
	//{
	//	x *= v.x;
	//	y *= v.y;
	//	z *= v.z;

	//	return *this;
	//}
	//Division
	inline Vector3 operator/(float s) const
	{
		VERIFY( s != 0, "[Math::Vector3 /] Cannot divide by zero!");
		return { x / s, y / s, z / s };
	}
	inline Vector3& operator/= (float s)
	{
		VERIFY(s != 0 ,"[Math::Vector3 /=] Cannot divide by zero!");
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	//inline Vector3 operator/(Vector3 v) const
	//{
	//	VERIFY(v.x != 0 || v.y != 0 || v.z != 0, "[Math::Vector3 /] Cannot divide by zero!");
	//	return { x / v.x, y / v.y, z / v.z };
	//}
	//inline Vector3& operator/= (Vector3 v)
	//{
	//	VERIFY(v.x != 0 || v.y != 0 || v.z != 0, "[Math::Vector3 /=] Cannot divide by zero!");
	//	x /= v.x;
	//	y /= v.y;
	//	z /= v.z;
	//	return *this;
	//}
};

}//namespace Math
}//namespace Engine

#endif // !INCLUDED_MATH_VECTOR3_H
