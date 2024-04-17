#include "Precompiled.h"
#include "SkinnedMesh.h"

using namespace SWGE;
using namespace Graphics;

SkinnedMesh::SkinnedMesh() noexcept
			: mVertices(nullptr)
			, mIndices(nullptr)
			, mNumVertices(0)
			, mNumIndices(0)
{
}

SkinnedMesh::~SkinnedMesh()
{
	ASSERT(mVertices == nullptr, "[Mesh] Verticies not Freed!");
	ASSERT(mIndices == nullptr, "[Mesh] Indicies not Freed!");
}

void SkinnedMesh::Allocate(uint32_t numVertices, uint32_t numIndices)
{
	ASSERT(numVertices > 0, "[Mesh] Invalid count.");
	ASSERT(numIndices > 0, "This shouldnt happen.");

	Destroy();

	mNumVertices = numVertices;
	mNumIndices = numIndices;

	mVertices = new BoneVertex[numVertices];
	mIndices = new uint32_t[numIndices];

}

void SkinnedMesh::Destroy()
{
	SafeDeleteArray(mIndices);
	SafeDeleteArray(mVertices);
	mNumVertices = 0;
	mNumIndices = 0;
}

BoneVertex& SkinnedMesh::GetVertex(uint32_t index)
{
	ASSERT(index < mNumVertices, "[Mesh] Invalid index.");
	return mVertices[index];

}
uint32_t& SkinnedMesh::GetIndex(uint32_t index)
{
	ASSERT(index < mNumIndices, "[Mesh] Invalid count.");
	return mIndices[index];
}
