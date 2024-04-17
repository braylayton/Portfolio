#include "Precompiled.h"
#include "Mesh.h"

using namespace SWGE;
using namespace Graphics;

Mesh::Mesh() noexcept
	: mVertices(nullptr)
	, mIndices(nullptr)
	, mNumVertices(0)
	, mNumIndices(0)
{
}

Mesh::~Mesh()
{
	ASSERT(mVertices == nullptr, "[Mesh] Verticies not Freed!");
	ASSERT(mIndices == nullptr, "[Mesh] Indicies not Freed!");
}

void Mesh::Allocate(uint32_t numVertices, uint32_t numIndices)
{
	ASSERT(numVertices > 0, "[Mesh] Invalid count.");
	ASSERT(numIndices > 0,  "This shouldnt happen.");

	Destroy();

	mNumVertices = numVertices;
	mNumIndices = numIndices;

	mVertices = new Vertex[numVertices];
	mIndices = new uint32_t[numIndices];

}

void Mesh::Destroy()
{
	SafeDeleteArray(mIndices);
	SafeDeleteArray(mVertices);
	mNumVertices = 0;
	mNumIndices = 0;
}

Vertex& Mesh::GetVertex(uint32_t index)
{
	ASSERT(index < mNumVertices, "[Mesh] Invalid index.");
	return mVertices[index];


}
uint32_t& Mesh::GetIndex(uint32_t index)
{
	ASSERT(index < mNumIndices , "[Mesh] Invalid count.");
	return mIndices[index];
}
