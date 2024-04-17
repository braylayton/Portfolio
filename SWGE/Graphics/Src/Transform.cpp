#include "Precompiled.h"
#include "Transform.h"

using namespace SWGE;
using namespace Graphics;

Math::Matrix4& Transform::GetTransform()
{
	//TODO: Add Euler to Quaternion and Matrix Rotation not just Rotationx,y,z
	if (mRotation.x == 0 && mRotation.y == 0 && mRotation.z == 0)
	{
		mWorld = ((Math::Matrix4::Scaling(mScale) * Math::QuaternionToMatrix4(mQuatRotation)) * Math::Matrix4::Translation(mPosition));
	}
	else
	{
		SetQuatRotation(Math::Matrix4ToQuaternion((Math::Matrix4::RotationX(mRotation.x) *  Math::Matrix4::RotationY(mRotation.y) * Math::Matrix4::RotationZ(mRotation.z))));
		mWorld = ((Math::Matrix4::Scaling(mScale) * Math::QuaternionToMatrix4(mQuatRotation)) * Math::Matrix4::Translation(mPosition));
	}
	return mWorld;
}