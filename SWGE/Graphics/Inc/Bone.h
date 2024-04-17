#ifndef INCLUDED_GRAPHICS_BONE_H
#define INCLUDED_GRAPHICS_BONE_H

namespace SWGE {
namespace Graphics {

class Bone
{
public:

	std::string name;

	Bone* parent;
	std::vector<Bone*> children;

	Math::Matrix4 transform;
	Math::Matrix4 offsetTransform;
	
	int mIndex;
	int parentIndex;
	std::vector<int> childrenIndex;
};

} // Graphics
} // SWGE

#endif // INCLUDED_GRAPHICS_BONE_H