#ifndef INCLUDED_GRAPHICS_VERTEXTYPES_H
#define INCLUDED_GRAPHICS_VERTEXTYPES_H

#define	VF_POSITION	0x1 << 0
#define	VF_NORMAL	0x1 << 1
#define	VF_TANGENT	0x1 << 2
#define	VF_COLOR	0x1 << 3
#define	VF_UV		0x1 << 4
#define	VF_BINDEX	0x1 << 5
#define VF_BWEIGHT	0x1 << 6

namespace SWGE {
namespace Graphics {

struct VertexP
{
	static const uint32_t Format = VF_POSITION;
	Math::Vector3 position;
};

struct VertexPC
{
	static const uint32_t Format = VF_POSITION | VF_COLOR;
	Math::Vector3 position;
	Math::Vector4 color;
};

struct VertexPT
{
	static const uint32_t Format = VF_POSITION | VF_UV;
	Math::Vector3 position;
	Math::Vector2 uv;
};

struct Vertex
{
	static const uint32_t Format = VF_POSITION | VF_NORMAL | VF_TANGENT | VF_UV;
	Math::Vector3 position;
	Math::Vector3 normal;
	Math::Vector3 tangent;
	Math::Vector2 UV;

};

struct BoneVertex
{
	static const uint32_t Format = VF_POSITION | VF_NORMAL | VF_TANGENT | VF_UV | VF_BINDEX | VF_BWEIGHT;
	Math::Vector3 position;
	Math::Vector3 normal;
	Math::Vector3 tangent;
	Math::Vector2 UV;
	int boneIndex[4] = {};
	int boneWeight[4] = {};

};



} // namespace SWGE
} // namespace Graphics
#endif // !INCLUDED_GRAPHICS_VERTEXTYPES_H