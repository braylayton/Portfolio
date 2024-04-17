#ifndef INCLUDED_GRAPHICS_ANIMATION_H
#define INCLUDED_GRAPHICS_ANIMATION_H

#include "Keyframe.h"

namespace SWGE {
namespace Graphics {

	class Animation 
	{
	friend class AnimationBuilder;
	public:
		Math::Matrix4 GetTransform(float time) const;
	private:
		std::vector<PositionKeyframe> mPositionKeyframes;
		std::vector<ScaleKeyframe> mScaleKeyframes;
		std::vector<RotationKeyframe> mRotationKeyframes;
	};


} // Graphics
} // SWGE

#endif // !INCLUDED_GRAPHICS_ANIMATION_H
