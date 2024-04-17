#ifndef INCLUDED_GRAPHICS_MESHBUILDER_H
#define INCLUDED_GRAPHICS_MESHBUILDER_H

namespace SWGE {
namespace Graphics {

class Mesh;
class SkinnedMesh;

class MeshBuilder
{
public:
	static void CreateCube(Mesh& mesh, Math::Vector3 offset = { 0,0,0 });
	static void CreateCylinder(Mesh& mesh, float radius, uint32_t slices, uint32_t rings);
	static void CreateCylinderSkinned(SkinnedMesh& mesh, float radius, uint32_t slices, uint32_t rings, Math::Vector3 offset = { 0,0,0 });
	static void CreateUVSphere(Mesh& mesh, uint32_t mSliceCount, uint32_t mStackCount);
	static void CreateSkyBox(Mesh& mesh);
	static void CreateIcoSphere(Mesh& mesh);
	static void CreatePlane(Mesh& mesh, uint32_t rows, uint32_t columns, float scale);

	static void ComputeNormals(Mesh& mesh);
	static Math::AABB ComputeBound(const Mesh& mesh);
};



} // Graphics
} // SWGE


#endif // INCLUDED_GRAPHICS_MESHBUILDER_H
