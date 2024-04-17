#ifndef INCLUDED_GRAPHICS_ANIMATIONBUILDER_H
#define INCLUDED_GRAPHICS_ANIMATIONBUILDER_H

#include <Math/Inc/QMath.h>
#include "Animation.h"
#include "BoneAnimation.h"

namespace SWGE {
namespace Graphics {

	class AnimationBuilder
	{
		public:
			AnimationBuilder& AddPositionKey(Math::Vector3 position, float time);
			AnimationBuilder& AddScaleKey(Math::Vector3 Scale, float time);
			AnimationBuilder& AddRotationKey(Math::Quaternion rotation, float time);
			AnimationBuilder& AddKey(Math::Vector3 position, Math::Vector3 scale, Math::Quaternion rotation,float time);
			Animation BuildAnimation();
		private:
			PositionKeyframe mPosKeyframe;
			ScaleKeyframe mScaleKeyframe;
			RotationKeyframe mRotKeyframe;

			Animation mAnimation;
	};

}
}

#endif // !INCLUDED_GRAPHICS_ANIMATIONBUILDER_H
