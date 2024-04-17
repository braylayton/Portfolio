#include "Precompiled.h"
#include "Animation.h"

using namespace SWGE;
using namespace Graphics;

Math::Matrix4 Animation::GetTransform(float time) const
{
	Math::Vector3 mPosition;
	Math::Vector3 mScale;
	Math::Quaternion mRotation;
	Math::Matrix4 mMatrix{ Math::Matrix4::Identity() };
	float t;

	if (time >= 0)
	{
		for (size_t i = 1; i < mPositionKeyframes.size(); i++)
		{
			if (time <= mPositionKeyframes[i].time)
			{
				t = (time - mPositionKeyframes[i - 1].time) / (mPositionKeyframes[i].time - mPositionKeyframes[i - 1].time);
				mPosition = Math::Lerp(mPositionKeyframes[i - 1].position, mPositionKeyframes[i].position, t);
				break;
			}
			
		} 

		for (size_t i = 1; i < mScaleKeyframes.size(); i++)
		{
			if (time <= mScaleKeyframes[i].time)
			{
				t = (time - mScaleKeyframes[i - 1].time) / (mScaleKeyframes[i].time - mScaleKeyframes[i - 1].time);
				mScale = Math::Lerp(mScaleKeyframes[i - 1].scale, mScaleKeyframes[i].scale, t);
				break;
			}
		}

		for (size_t i = 1; i < mRotationKeyframes.size(); i++)
		{
			if (time <= mRotationKeyframes[i].time)
			{
				t = (time - mRotationKeyframes[i - 1].time) / (mRotationKeyframes[i].time - mRotationKeyframes[i - 1].time);
				mRotation = Math::Slerp(mRotationKeyframes[i - 1].rotation, mRotationKeyframes[i].rotation, t);
				break;
			}
		}
	}

	mMatrix = Math::QuaternionToMatrix4(mRotation);
	mMatrix = mMatrix * Math::Matrix4::Scaling(mScale);
	mMatrix = mMatrix * Math::Matrix4::Translation(mPosition);
	return mMatrix;


}