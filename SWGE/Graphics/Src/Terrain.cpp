#include "Precompiled.h"
#include "Terrain.h"

using namespace SWGE;
using namespace Graphics;

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::Initialize(const char* filename, uint32_t columns, uint32_t rows, float maxHeight)
{
	mHeightMap.GenerateFromRAW(filename, columns, rows);

	uint32_t numVertices = columns * rows;
	uint32_t numTiles = (columns - 1) * (rows - 1);
	uint32_t numIndices = numTiles * 6;

	mMesh.Allocate(numVertices, numIndices);
	// double for loop, and set vertex x ,y ,z

	//fill the vertices (pixels and vertices are 1:1)
	float uStep = 1.0f / (columns - 1);
	float vStep = 1.0f / (rows - 1);
	
	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			uint32_t index = x + (z*columns);
			float height = mHeightMap.GetHeight(x, z) * maxHeight;
			auto& vertex = mMesh.GetVertex(index);
			vertex.position = { (float)x, height, (float)z };
			vertex.normal = Math::Vector3::YAxis();
			vertex.UV = { x * uStep, z * vStep };
		}
	}

	ComputeNormal(columns, rows);
	//Homework!
	//ComputeNormal();
	//ComputeTangent();
	uint32_t index = 0;
	//Fill Indices
	for (uint32_t z = 0; z < rows - 1; ++z)
	{
		for (uint32_t x = 0; x < columns - 1; ++x)
		{
			//1---3
			//| / |
			//0---2
			mMesh.GetIndex(index++) = (x    ) + ((z    ) * columns);
			mMesh.GetIndex(index++) = (x    ) + ((z + 1) * columns);
			mMesh.GetIndex(index++) = (x + 1) + ((z    ) * columns);
											  
			mMesh.GetIndex(index++) = (x    ) + ((z + 1) * columns);
			mMesh.GetIndex(index++) = (x + 1) + ((z + 1) * columns);
			mMesh.GetIndex(index++) = (x + 1) + ((z    ) * columns);
		}
	}


	mMeshBuffer.Initialize(mMesh, true);
}

void Terrain::Terminate()
{
	mMeshBuffer.Terminate();
	mMesh.Destroy();
	mHeightMap.Clear();
}

void Terrain::Render() const
{
	mMeshBuffer.Render();
}

void Terrain::ComputeNormal(uint32_t columns , uint32_t rows)
{
	for (uint32_t z = 0; z < rows - 2; ++z)
	{
		for (uint32_t x = 0; x < columns - 2; ++x)
		{
			uint32_t index = x + (z * columns);
			uint32_t xVertexIndex = index++;
			uint32_t zVertexIndex = index + 1 + columns;

			auto& vertex = mMesh.GetVertex(index);
			auto& xVertex = mMesh.GetVertex(xVertexIndex);
			auto& zVertex = mMesh.GetVertex(zVertexIndex);


			vertex.normal = Math::Normalize(Math::Cross(xVertex.position - vertex.position, zVertex.position - vertex.position));
			vertex.tangent = Math::Normalize(zVertex.position - vertex.position);
			/*Math::Vector3 varX(1.0f, 0.0f, (x + 1, z) - mHeightMap.GetHeight(x - 1, z));
			Math::Vector3 varY(1.0f, 0.0f, (x, z + 1) - mHeightMap.GetHeight(x, z - 1));
			Math::Vector3 Norm = Math::Normalize(Math::Cross(varX, varY));*/

		}
	}

	/*
	i<numindicies
	for(i for 0 to indicies)
	{
		vertex[i[i+0]].pos
		vertex[i[i+1]].pos
		vertex[i[i+2]].pos
		cross();

		vertex[i[i+0]].n = n;
		vertex[i[i+0]].n = n;
		vertex[i[i+0]].n = n;
	}
	 to normalize();
	for
	{
		                                                   normalize();
	}
	*/
}


//Math::Vector3 ComputeTangent()
//{
//
//}