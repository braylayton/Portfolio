#pragma once

#include "Bone.h"
#include "BoneAnimation.h"
#include "Math/Inc/QMath.h"

namespace SWGE {
namespace Graphics {

class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

	void GetTransform(float time, Bone* bone, Math::Matrix4& transform) const; // could pass the bone index uint32_t boneIndex;

	BoneAnimation boneAnimation;
	std::string name;
	float duration;
	float ticksPerSecond;
};


} // Graphics
} // SWGE