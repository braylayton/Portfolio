#include "Precompiled.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "SkinnedMesh.h"

using namespace SWGE;
using namespace Graphics;


void MeshBuilder::CreateCube(Mesh& mesh, Math::Vector3 offset)
{
	float Xlength = 1, YHeight = 1, ZWidth = 1;
	mesh.Allocate(24, 36);
	
	static const Graphics::Vertex kVertices[] =
	{
		//Front
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth) + offset,	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(0,0) },	//top left 0 
		{ Math::Vector3(Xlength,  YHeight,	-ZWidth) + offset,	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 1
		{ Math::Vector3(Xlength,  -YHeight,	-ZWidth) + offset,	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 2
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth) + offset,	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(0,1) },	//bot left 3
		//Back																																								//Back											 				 					    
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth) + offset,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, ZWidth)),	 Math::Vector2(0,0) },	//top left 4
		{ Math::Vector3(Xlength,   YHeight,  ZWidth) + offset,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, ZWidth)),	 Math::Vector2(1,0) },	//top right 5
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth) + offset,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, ZWidth)),	 Math::Vector2(1,1) },	//bot right 6
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth) + offset,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, ZWidth)),	 Math::Vector2(0,1) },	//bot left 7
		//Top											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth) + offset,	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)), Math::Vector2(0,0) },	//top left 8 
		{ Math::Vector3(Xlength,   YHeight,	 ZWidth) + offset,	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight,  ZWidth)), Math::Vector2(1,0) },	//top right 9
		{ Math::Vector3(Xlength,   YHeight,	-ZWidth) + offset,	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 10
		{ Math::Vector3(-Xlength,  YHeight, -ZWidth) + offset,	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(0,1) },	//bot left 11
																																									//Bottom											   				 					    
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth) + offset,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(0,0) },	//top left 12
		{ Math::Vector3(Xlength,  -YHeight, -ZWidth) + offset,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 13
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth) + offset,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight,  ZWidth)), Math::Vector2(1,1) },	//bot right 14
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth) + offset,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)), Math::Vector2(0,1) },	//bot left 15
																																									//Left											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth) + offset,	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)), Math::Vector2(0,0) },	//top left 16
		{ Math::Vector3(-Xlength,  YHeight,	-ZWidth) + offset,	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 17
		{ Math::Vector3(-Xlength, -YHeight,	-ZWidth) + offset,	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 18
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth) + offset,	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)), Math::Vector2(0,1) },	//bot left 19
																																									//Right											   				 					    
		{ Math::Vector3(Xlength,  YHeight, -ZWidth)	 + offset,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight, -ZWidth)),	 Math::Vector2(0,0) },	//top left 20
		{ Math::Vector3(Xlength,  YHeight,  ZWidth)	 + offset,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight,  ZWidth)),	 Math::Vector2(1,0) },	//top right 21
		{ Math::Vector3(Xlength, -YHeight,  ZWidth)	 + offset,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight,  ZWidth)),	 Math::Vector2(1,1) },	//bot right 22
		{ Math::Vector3(Xlength, -YHeight, -ZWidth)	 + offset,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight, -ZWidth)),	 Math::Vector2(0,1) },	//bot left 23
	};
	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	std::memcpy(mesh.mVertices, kVertices, sizeof(Graphics::Vertex) * kVertexCount);

	static const uint32_t kIndices[] = 
	{
		//Front
		0,1,2,
		0,2,3,
		//Back good
		5,4,7,
		5,7,6,
		//Top	good
		8,9,10,		//8,11,10,8,10,9,
		8,10,11,
		//Bot
		12,13,14,
		12,14,15,
		//Left good
		16,17,18,
		16,18,19,
		//Right
		20,21,22,
		20,22,23

	};

	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);
	std::memcpy(mesh.mIndices, kIndices, sizeof(uint32_t) * kIndexCount);
}

void MeshBuilder::CreateUVSphere(Mesh& mesh, uint32_t mSliceCount, uint32_t mStackCount)
{
	float mRadius = 1.0f;

	uint32_t size = mSliceCount * mStackCount;

	std::vector<Graphics::Vertex> kSphereVertices; 
	std::vector<uint32_t> kSphereIndices;
	float mPhiStep = Math::kPi / mStackCount;
	float mThetaStep = Math::kTwoPi / mSliceCount;

	Graphics::Vertex tempVertex;
	//Vertices
	//Top Vertex
	tempVertex = { Math::Vector3(0.0f, mRadius, 0.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(0.0f, 0.0f) };
	kSphereVertices.push_back(tempVertex);

	mesh.Allocate(((mSliceCount + 1) * (mSliceCount + 1)), ((6 * mStackCount) * (mSliceCount)));
	for (uint32_t i = 1; i <=  mStackCount - 1; i++)
	{
		float mPhi = mPhiStep * i;
		for (uint32_t j = 0; j <= mSliceCount; j++)
		{
			float mTheta = mThetaStep * j;
	
			Math::Vector3 mPosition;
			mPosition.x = (mRadius * sin(mPhi) * cos(mTheta));
			mPosition.y = (mRadius * cos(mPhi));
			mPosition.z = (mRadius * sin(mPhi) * sin(mTheta));

			Math::Vector3 mNormal = Math::Normalize(mPosition);
			Math::Vector3 mTangent;
			mTangent.x = (-mRadius*sin(mPhi)*sin(mTheta));
			mTangent.y = (0.0f);
			mTangent.z = (mRadius*sin(mPhi)*cos(mTheta));
			Math::Vector2 mUV = Math::Vector2(mTheta / Math::kTwoPi, mPhi / Math::kPi);

			tempVertex = { mPosition, mNormal, Math::Normalize(mTangent), mUV };
			kSphereVertices.push_back(tempVertex);

		}

	}

	//Bot Vertex
	tempVertex = { Math::Vector3(0.0f, -mRadius, 0.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(0.0f, 1.0f) };
	kSphereVertices.push_back(tempVertex);
	

	for (uint32_t i = 1; i <= mSliceCount; ++i)
	{
		kSphereIndices.push_back(0);
		kSphereIndices.push_back(i + 1);
		kSphereIndices.push_back(i);
	}

	uint32_t mBaseIndex = 1;
	uint32_t mRingVertexCount = mSliceCount + 1;

	for (uint32_t i = 0; i < mStackCount - 2; i++)
	{
		for (uint32_t j = 0; j < mSliceCount; j++)
		{
			kSphereIndices.push_back(mBaseIndex + i * mRingVertexCount + j);
			kSphereIndices.push_back(mBaseIndex + i *mRingVertexCount + (j + 1));
			kSphereIndices.push_back(mBaseIndex + (i + 1) * mRingVertexCount + j);

			kSphereIndices.push_back(mBaseIndex + (i + 1) * mRingVertexCount + j);
			kSphereIndices.push_back(mBaseIndex + i * mRingVertexCount + (j + 1));
			kSphereIndices.push_back(mBaseIndex + (i + 1) * mRingVertexCount + (j + 1));
		}
	}

	uint32_t mSouthPoleIndex = static_cast<uint32_t>(kSphereVertices.size()) - 1;

	mBaseIndex = mSouthPoleIndex - mRingVertexCount;

	for (uint32_t i = 0; i < mSliceCount; ++i)
	{
		kSphereIndices.push_back(mSouthPoleIndex);
		kSphereIndices.push_back(mBaseIndex + i);
		kSphereIndices.push_back(mBaseIndex + i + 1);
	}

	for (uint32_t i = 0; i < kSphereVertices.size(); i++)
	{
		mesh.mVertices[i] = kSphereVertices[i];
	}
	for (uint32_t i = 0; i < kSphereIndices.size(); i++)
	{
		mesh.mIndices[i] = kSphereIndices[i];
	}
	
}

static void CreateIcoSphere(Mesh& mesh)
{

	float var = (1.0f + Math::Sqrt(5.0f)) / 2.0f;

	/*const Graphics::Vertex icoVertices[] = 
	{
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)),	Math::Vector4::White(), Math::Vector2(0,0) }
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)),	Math::Vector4::White(), Math::Vector2(0,0) }
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)),	Math::Vector4::White(), Math::Vector2(0,0) }
	};*/

	const uint32_t icoIndicies[]
	{
		0,1,2,
		0,2,3,
		//Back good
		5,4,7,
		5,7,6,
		//Top	good
		8,9,10,		//8,11,10,8,10,9,
		8,10,11,
		//Bot
		12,13,14,
		12,14,15,
		//Left good
		16,17,18,
		16,18,19,
		//Right
		20,21,22,
		20,22,23
	};
}

void MeshBuilder::CreateSkyBox(Mesh& mesh)
{
	float Xlength = 50000, YHeight = 50000, ZWidth = 50000;

	const uint32_t kNumVertices = 24;
	const uint32_t kNumIndices = 36;

	mesh.Allocate(kNumVertices, kNumIndices);

	static const Graphics::Vertex kVertices[] =
	{
		//Front
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(0,0) },	//top left 0 
		{ Math::Vector3(Xlength,  YHeight,	-ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 1
		{ Math::Vector3(Xlength,  -YHeight,	-ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 2
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(0,1) },	//bot left 3
																																									//Back																																															//Back											 				 					    
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth),	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, ZWidth)),	 Math::Vector2(0,0) },	//top left 4
		{ Math::Vector3(Xlength,   YHeight,  ZWidth),	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, ZWidth)),	 Math::Vector2(1,0) },	//top right 5
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth),	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, ZWidth)),	 Math::Vector2(1,1) },	//bot right 6
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth),	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, ZWidth)),	 Math::Vector2(0,1) },	//bot left 7
																																									//Top											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)), Math::Vector2(0,0) },	//top left 8 
		{ Math::Vector3(Xlength,   YHeight,	 ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight,  ZWidth)), Math::Vector2(1,0) },	//top right 9
		{ Math::Vector3(Xlength,   YHeight,	-ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 10
		{ Math::Vector3(-Xlength,  YHeight, -ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(0,1) },	//bot left 11
																																									//Bottom											   				 					    
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth),	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(0,0) },	//top left 12
		{ Math::Vector3(Xlength,  -YHeight, -ZWidth),	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 13
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth),	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight,  ZWidth)), Math::Vector2(1,1) },	//bot right 14
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth),	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)), Math::Vector2(0,1) },	//bot left 15
																																									//Left											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)), Math::Vector2(0,0) },	//top left 16
		{ Math::Vector3(-Xlength,  YHeight,	-ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)), Math::Vector2(1,0) },	//top right 17
		{ Math::Vector3(-Xlength, -YHeight,	-ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)), Math::Vector2(1,1) },	//bot right 18
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)), Math::Vector2(0,1) },	//bot left 19
																																									//Right											   				 					    
		{ Math::Vector3(Xlength,  YHeight, -ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight, -ZWidth)),	 Math::Vector2(0,0) },	//top left 20
		{ Math::Vector3(Xlength,  YHeight,  ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight,  ZWidth)),	 Math::Vector2(1,0) },	//top right 21
		{ Math::Vector3(Xlength, -YHeight,  ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight,  ZWidth)),	 Math::Vector2(1,1) },	//bot right 22
		{ Math::Vector3(Xlength, -YHeight, -ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight, -ZWidth)),	 Math::Vector2(0,1) },	//bot left 23
	};
	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	std::memcpy(mesh.mVertices, kVertices, sizeof(Graphics::Vertex) * kVertexCount);

	static const uint32_t kIndices[] =
	{
		//Front
		2,1,0,
		3,2,0,
		//Back good
		7,4,5,
		6,7,5,
		//Top	good
		10,9,8,		//8,11,10,8,10,9,
		11,10,8,
		//Bot
		14,13,12,
		15,14,12,
		//Left good
		18,17,16,
		19,18,16,
		//Right
		22,21,20,
		23,22,20

	};

	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);
	std::memcpy(mesh.mIndices, kIndices, sizeof(uint32_t) * kIndexCount);
}

void MeshBuilder::CreateCylinder(Mesh& mesh, float radius, uint32_t slices, uint32_t rings)
{

	std::vector<Graphics::Vertex> kCylinVertices; //= new Graphics::Vertex[(mStackCount + 1) * (mSliceCount + 1)];
	std::vector<uint32_t> kCylinIndices;
	const uint32_t kNumVertices = (slices + 1) * rings;
	const uint32_t kNumIndices = slices * (rings - 1) * 6;
	const float kSliceStep = Math::kTwoPi / slices;
	const float kRingStep = 2.0f / (rings - 1);

	mesh.Allocate(kNumVertices, kNumIndices);
	Graphics::Vertex tempVertex;

	// Fill vertex data
	float uStep = 1.0f / slices;
	float vStep = 1.0f / rings;
	uint32_t index = 0;
	for (uint32_t j = 0; j < rings; ++j)
	{
		for (uint32_t i = 0; i <= slices; ++i)
		{
			const float theta = i * kSliceStep;
			const float y = 1.0f - (j * kRingStep);
			const float s = sin(theta);
			const float c = cos(theta);
			const float x = radius * c;
			const float z = radius * s;
			tempVertex.position = Math::Vector3(x, y, z);
			tempVertex.normal = Math::Vector3(x, 0.0f, z);
			tempVertex.tangent = Math::Vector3(-s, 0.0f, c);
			tempVertex.UV = Math::Vector2(i * uStep, j * vStep);
			kCylinVertices.push_back(tempVertex);
		}
	}

	// Fill index data
	index = 0;
	for (uint32_t j = 0; j < rings - 1; ++j)
	{
		for (uint32_t i = 0; i < slices; ++i)
		{
			const uint32_t a = i % (slices + 1);
			const uint32_t b = (i + 1) % (slices + 1);
			const uint32_t c = j * (slices + 1);
			const uint32_t d = (j + 1) * (slices + 1);

			//     a     b
			//   c +-----+
			//     |     |
			//     |     |
			//   d +-----+
			//
			kCylinIndices.push_back(a + c);
			kCylinIndices.push_back(b + c);
			kCylinIndices.push_back(a + d);

			kCylinIndices.push_back(b + c);
			kCylinIndices.push_back(b + d);
			kCylinIndices.push_back(a + d);
		}
	}

	for (uint32_t i = 0; i < kCylinVertices.size(); i++)
	{
		mesh.mVertices[i] = kCylinVertices[i];
	}
	for (uint32_t i = 0; i < kCylinIndices.size(); i++)
	{
		mesh.mIndices[i] = kCylinIndices[i];
	}
}

//
//void MeshBuilder::CreateCylinderSkinned(SkinnedMesh& skinnedmesh, float radius, uint32_t slices, uint32_t rings, Math::Vector3 offset)
//{
//	std::vector<Graphics::Vertex> kCylinVertices; //= new Graphics::Vertex[(mStackCount + 1) * (mSliceCount + 1)];
//	std::vector<uint32_t> kCylinIndices;
//	const uint32_t kNumVertices = (slices + 1) * rings;
//	const uint32_t kNumIndices = slices * (rings - 1) * 6;
//	const float kSliceStep = Math::kTwoPi / slices;
//	const float kRingStep = 2.0f / (rings - 1);
//
//	skinnedmesh.Allocate(kNumVertices, kNumIndices);
//	Graphics::Vertex tempVertex;
//
//	// Fill vertex data
//	float uStep = 1.0f / slices;
//	float vStep = 1.0f / rings;
//	uint32_t index = 0;
//	for (uint32_t j = 0; j < rings; ++j)
//	{
//		for (uint32_t i = 0; i <= slices; ++i)
//		{
//			const float theta = i * kSliceStep;
//			const float y = 1.0f - (j * kRingStep);
//			const float s = sin(theta);
//			const float c = cos(theta);
//			const float x = radius * c;
//			const float z = radius * s;
//			tempVertex.position = Math::Vector3(x, y, z) + offset;
//			tempVertex.normal = Math::Vector3(x, 0.0f, z);
//			tempVertex.tangent = Math::Vector3(-s, 0.0f, c);
//			tempVertex.UV = Math::Vector2(i * uStep, j * vStep);
//			kCylinVertices.push_back(tempVertex);
//		}
//	}
//
//	// Fill index data
//	index = 0;
//	for (uint32_t j = 0; j < rings - 1; ++j)
//	{
//		for (uint32_t i = 0; i < slices; ++i)
//		{
//			const uint32_t a = i % (slices + 1);
//			const uint32_t b = (i + 1) % (slices + 1);
//			const uint32_t c = j * (slices + 1);
//			const uint32_t d = (j + 1) * (slices + 1);
//
//			//     a     b
//			//   c +-----+
//			//     |     |
//			//     |     |
//			//   d +-----+
//			//
//			kCylinIndices.push_back(a + c);
//			kCylinIndices.push_back(b + c);
//			kCylinIndices.push_back(a + d);
//
//			kCylinIndices.push_back(b + c);
//			kCylinIndices.push_back(b + d);
//			kCylinIndices.push_back(a + d);
//		}
//	}
//
//	for (uint32_t i = 0; i < kCylinVertices.size(); i++)
//	{
////		skinnedmesh.mVertices[i] = kCylinVertices[i];
//	}
//	for (uint32_t i = 0; i < kCylinIndices.size(); i++)
//	{
//		skinnedmesh.mIndices[i] = kCylinIndices[i];
//	}
//}

//void MeshBuilder::CreateCone(Mesh& mesh, float radius, uint32_t slices, uint32_t rings)
//{
//
//	std::vector<Graphics::Vertex> kCylinVertices; //= new Graphics::Vertex[(mStackCount + 1) * (mSliceCount + 1)];
//	std::vector<uint32_t> kCylinIndices;
//	const uint32_t kNumVertices = (slices + 1) * rings;
//	const uint32_t kNumIndices = slices * (rings - 1) * 6;
//	const float kSliceStep = Math::kTwoPi / slices;
//	const float kRingStep = 2.0f / (rings - 1);
//	const float radiusStep = (topRadius - bottomRadius) / rings;
//	mesh.Allocate(kNumVertices, kNumIndices);
//	Graphics::Vertex tempVertex;
//
//	// Fill vertex data
//	float uStep = 1.0f / slices;
//	float vStep = 1.0f / rings;
//	uint32_t index = 0;
//	for (uint32_t j = 0; j < rings; ++j)
//	{
//		for (uint32_t i = 0; i <= slices; ++i)
//		{
//			const float theta = i * kSliceStep;
//			const float y = 1.0f - (j * kRingStep);
//			const float s = sin(theta);
//			const float c = cos(theta);
//			const float x = radius * c;
//			const float z = radius * s;
//			tempVertex.position = Math::Vector3(x, y, z);
//			tempVertex.normal = Math::Vector3(x, 0.0f, z);
//			tempVertex.tangent = Math::Vector3(-s, 0.0f, c);
//			tempVertex.UV = Math::Vector2(i * uStep, j * vStep);
//			kCylinVertices.push_back(tempVertex);
//		}
//	}
//
//	// Fill index data
//	index = 0;
//	for (uint32_t j = 0; j < rings - 1; ++j)
//	{
//		for (uint32_t i = 0; i < slices; ++i)
//		{
//			const uint32_t a = i % (slices + 1);
//			const uint32_t b = (i + 1) % (slices + 1);
//			const uint32_t c = j * (slices + 1);
//			const uint32_t d = (j + 1) * (slices + 1);
//
//			//     a     b
//			//   c +-----+
//			//     |     |
//			//     |     |
//			//   d +-----+
//			//
//			kCylinIndices.push_back(a + c);
//			kCylinIndices.push_back(b + c);
//			kCylinIndices.push_back(a + d);
//
//			kCylinIndices.push_back(b + c);
//			kCylinIndices.push_back(b + d);
//			kCylinIndices.push_back(a + d);
//		}
//	}
//
//	for (uint32_t i = 0; i < kCylinVertices.size(); i++)
//	{
//		mesh.mVertices[i] = kCylinVertices[i];
//	}
//	for (uint32_t i = 0; i < kCylinIndices.size(); i++)
//	{
//		mesh.mIndices[i] = kCylinIndices[i];
//	}
//}

void MeshBuilder::CreatePlane(Mesh& mesh, uint32_t rows, uint32_t columns, float scale)
{
	ASSERT(rows > 1 && columns > 1, "[MeshBuilder] Invalid parameters.");

	const uint32_t kNumVertices = rows * columns;
	const uint32_t kNumIndices = (rows - 1) * (columns - 1) * 6;

	mesh.Allocate(kNumVertices, kNumIndices);

	const float posOffsetX = scale * -0.5f;
	const float posOffsetZ = scale * -0.5f;
	const float xStep = scale / (columns - 1);
	const float zStep = scale / (rows - 1);
	const float uStep = 1.0f / (columns - 1);
	const float vStep = 1.0f / (rows - 1);

	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			const uint32_t index = x + (z * columns);
			mesh.GetVertex(index).position = Math::Vector3(posOffsetX + (x * xStep), 0.0f, posOffsetZ + (z * zStep));
			mesh.GetVertex(index).normal = Math::Vector3::YAxis();
			mesh.GetVertex(index).tangent = Math::Vector3::XAxis();
			mesh.GetVertex(index).UV = Math::Vector2(x * uStep, z * vStep);
		}
	}

	uint32_t index = 0;
	for (uint32_t z = 0; z < rows - 1; ++z)
	{
		for (uint32_t x = 0; x < columns - 1; ++x)
		{
			mesh.GetIndex(index++) = (x + 0) + ((z + 0) * columns);
			mesh.GetIndex(index++) = (x + 0) + ((z + 1) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 1) * columns);

			mesh.GetIndex(index++) = (x + 0) + ((z + 0) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 1) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 0) * columns);
		}
	}
}

void SWGE::Graphics::MeshBuilder::ComputeNormals(Mesh& mesh)
{
	/*
	Need to finish
	for (uint32_t i = 0; i < mesh.GetVertexCount; i + 3)
	{
		Math::Normalize(mesh.mVertices[i].normal + mesh.mVertices[i + 1].normal + mesh.mVertices[i + 2].normal);
	}*/
}

Math::AABB SWGE::Graphics::MeshBuilder::ComputeBound(const Mesh& mesh)
{
	return Math::AABB();
}
