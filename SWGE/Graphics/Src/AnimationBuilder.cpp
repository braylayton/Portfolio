#include "Precompiled.h"
#include "AnimationBuilder.h"
#include "Keyframe.h"

using namespace SWGE;
using namespace Graphics;

AnimationBuilder& AnimationBuilder::AddPositionKey(Math::Vector3 position, float time)
{
	mPosKeyframe.position = position;
	mPosKeyframe.time = time;
	mAnimation.mPositionKeyframes.push_back(mPosKeyframe);

	return *this;
}
AnimationBuilder& AnimationBuilder::AddScaleKey(Math::Vector3 scale, float time)
{
	mScaleKeyframe.scale = scale;
	mScaleKeyframe.time = time;
	mAnimation.mScaleKeyframes.push_back(mScaleKeyframe);

	return *this;
}
AnimationBuilder& AnimationBuilder::AddRotationKey(Math::Quaternion rotation, float time)
{
	mRotKeyframe.rotation = rotation;
	mRotKeyframe.time = time;
	mAnimation.mRotationKeyframes.push_back(mRotKeyframe);
	
	return *this;
}
AnimationBuilder& AnimationBuilder::AddKey(Math::Vector3 position, Math::Vector3 scale, Math::Quaternion rotation, float time)
{
	mPosKeyframe.position = position;
	mPosKeyframe.time = time;
	mAnimation.mPositionKeyframes.push_back(mPosKeyframe);

	mScaleKeyframe.scale = scale;
	mScaleKeyframe.time = time;
	mAnimation.mScaleKeyframes.push_back(mScaleKeyframe);
	
	mRotKeyframe.rotation = rotation;
	mRotKeyframe.time = time;
	mAnimation.mRotationKeyframes.push_back(mRotKeyframe);
	


	return *this;
}
Animation AnimationBuilder::BuildAnimation()
{
	return std::move(mAnimation);
}