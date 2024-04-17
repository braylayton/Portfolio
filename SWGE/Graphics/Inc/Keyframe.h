#ifndef INCLUDED_GRAPHICS_KEYFRAME_H
#define INCLUDED_GRAPHICS_KEYFRAME_H

#include <Math/Inc/QMath.h>

namespace SWGE {
namespace Graphics {

struct PositionKeyframe
{
	Math::Vector3 position;
	float time;
};

struct ScaleKeyframe
{
	Math::Vector3 scale;
	float time;
};

struct RotationKeyframe
{
	Math::Quaternion rotation;
	float time;
};

} // Graphics
} // SWGE
#endif // !INCLUDED_GRAPHICS_KEYFRAME_H
