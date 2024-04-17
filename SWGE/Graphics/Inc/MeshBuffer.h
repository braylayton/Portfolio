#ifndef INCLUDED_GRAPHICS_MESHBUFFER_H
#define INCLUDED_GRAPHICS_MESHBUFFER_H

#include <Core/Inc/Core.h>

namespace SWGE {
namespace Graphics {

class Mesh;
class SkinnedMesh;

class MeshBuffer
{
public:
	MeshBuffer()noexcept;
	~MeshBuffer();
	
	MeshBuffer(const MeshBuffer&) = delete;
	MeshBuffer& operator=(const MeshBuffer&) = delete;

	MeshBuffer(MeshBuffer&&) = default;
	MeshBuffer&	operator=(MeshBuffer&&) = default;

	void Initialize(const Mesh& mesh, bool dynamic);
	void Initialize(const SkinnedMesh& skinmesh, bool dynamic);
	//void Initialize(const void* verticies, uint32_t vertexsize, uint32_t vertexcount,const uint32_t* indicies, uint32_t indexcount);
	void Initialize(const void* vertexData, uint32_t vertexSize, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices, bool dynamic = false);
	void Initialize(void* verticies, uint32_t vertexsize, uint32_t vertexcount);
	void Terminate();
	void Render() const;
private:
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;

	uint32_t mSize;
	uint32_t mVertexCount;
	uint32_t mIndexCount;

	bool mDynamic;
};

}//SWGE
}//Graphics

#endif //INCLUDED_GRAPHICS_MESHBUFFER_H