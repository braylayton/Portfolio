#pragma once
#include "Keyframe.h"

namespace SWGE {
namespace Graphics {

class BoneAnimation
{

public:
	Math::Matrix4 GetTransform(float time) const;
private:
	std::vector<PositionKeyframe> mPositionKeyframes;
	std::vector<ScaleKeyframe> mScaleKeyframes;
	std::vector<RotationKeyframe> mRotationKeyframes;

};

} // SWGE
} // Graphics