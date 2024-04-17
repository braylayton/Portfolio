#ifndef INCLUDED_GRAPHICS_SKINNEDMESH_H
#define INCLUDED_GRAPHICS_SKINNEDMESH_H

#include "VertexTypes.h"

namespace SWGE {
namespace Graphics {
class SkinnedMesh
{
	friend class MeshBuilder;
public:
	SkinnedMesh() noexcept;
	~SkinnedMesh();
	SkinnedMesh(const SkinnedMesh&) = delete;
	SkinnedMesh& operator=(const SkinnedMesh&) = delete;
	SkinnedMesh(SkinnedMesh&&) = default;
	SkinnedMesh& operator=(SkinnedMesh&&) = default;

	void Allocate(uint32_t numVertices, uint32_t numIndices);
	void Destroy();

	BoneVertex& GetVertex(uint32_t index);
	uint32_t& GetIndex(uint32_t index);

	BoneVertex*	GetVertices()				{ return mVertices; }
	const BoneVertex*	GetVertices() const { return mVertices; }
	const uint32_t* GetIndices() const		{ return mIndices; }
	uint32_t* GetIndices()					{ return mIndices; }
	uint32_t GetVertexCount()	const		{ return mNumVertices; }
	uint32_t GetIndexCount()	const		{ return mNumIndices; }

	void SetVertexCount(BoneVertex* temp)	{ mVertices = temp; }
	void SetIndicieCount(uint32_t* temp)	{ mIndices = temp; }

private:

	BoneVertex* mVertices;
	uint32_t* mIndices;

	uint32_t mNumVertices;
	uint32_t mNumIndices;
};

} // Graphics
} // SWGE

#endif // INCLUDED_GRAPHICS_SKINNEDMESH_H