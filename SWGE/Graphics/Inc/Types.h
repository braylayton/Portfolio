#ifndef INCLUDED_GRAPHICS_TYPES_H
#define INCLUDED_GRAPHICS_TYPES_H

namespace SWGE {
namespace Graphics{

enum class RenderPass 
{
	Opaque,
	Transparent,
	Custom
};

enum class CullMode
{
	Front,
	Back,
	None
};

enum class FillMode
{
	Solid,
	WireFrame
};
enum class ColorFormat
{
	RGBA_U8,
	RGBA_U32,
	RGBA_F16,
	R_S32,
	R_F16
};

}
}

#endif // !INCLUDED_GRAPHICS_TYPES_H
