#ifndef INCLUDED_GRAPHICS_TERRAIN_H
#define INCLUDED_GRAPHICS_TERRAIN_H

#include "HeightMap.h"
#include "Mesh.h"
#include "MeshBuffer.h"

namespace SWGE {
namespace Graphics{

class Terrain
{
public:
	Terrain();
	~Terrain();

	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;

	void Initialize(const char* filename, uint32_t columns, uint32_t rows, float maxHeight);
	void Terminate();
	

	void Render() const;

private:
	void ComputeNormal(uint32_t columns, uint32_t rows);
	Math::Vector3 ComputeTanget(int x, int z);
	float GetHeight(int x, int z);
	HeightMap mHeightMap;
	Mesh mMesh;
	MeshBuffer mMeshBuffer;
};



}
}



#endif