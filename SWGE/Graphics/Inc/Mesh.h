#ifndef INCLUDED_GRAPHICS_MESH_H
#define INCLUDED_GRAPHICS_MESH_H

#include "VertexTypes.h"

namespace SWGE{ 
namespace Graphics{
class Mesh
{
	friend class MeshBuilder;
public:
	Mesh() noexcept;
	~Mesh();
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	// Allows It to be moved not just non copyable
	//Mesh(Mesh&&) = default;
	Mesh(Mesh&& other) noexcept
	{
		mVertices = other.mVertices;
		mIndices = other.mIndices;
		mNumVertices = other.mNumVertices;
		mNumIndices = other.mNumIndices;

		other.mVertices = nullptr;
		other.mIndices = nullptr;
		other.mNumVertices = 0;
		other.mNumIndices = 0;
	}
	
	// Allows It to be moved not just non copyable
	//Mesh& operator=(Mesh&&) = default; 
	Mesh& operator=(Mesh&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		mVertices = other.mVertices;
		mIndices = other.mIndices;
		mNumVertices = other.mNumVertices;
		mNumIndices = other.mNumIndices;

		other.mVertices = nullptr;
		other.mIndices = nullptr;
		other.mNumVertices = 0;
		other.mNumIndices = 0;
		return *this;
	}

	void Allocate(uint32_t numVertices, uint32_t numIndices);
	void Destroy();

	Vertex& GetVertex(uint32_t index);
	uint32_t& GetIndex(uint32_t index);

	Vertex*	GetVertices()				{ return mVertices; }
	const Vertex*	GetVertices() const { return mVertices; }
	const uint32_t* GetIndices() const	{ return mIndices; }
	uint32_t* GetIndices()				{ return mIndices; }
	uint32_t GetVertexCount()	const	{ return mNumVertices; }
	uint32_t GetIndexCount()	const	{ return mNumIndices; }

	void SetVertexCount(Vertex* temp)	{ mVertices = temp; }
	void SetIndicieCount(uint32_t* temp) { mIndices = temp; }
	

private:
	
	Vertex* mVertices;
	uint32_t* mIndices;

	uint32_t mNumVertices;
	uint32_t mNumIndices;
};




}
}







#endif // INCLUDED_GRAPHICS_MESH_H
