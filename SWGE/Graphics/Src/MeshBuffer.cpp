#include "Precompiled.h"
#include "MeshBuffer.h"
#include "GraphicsSystem.h"
#include "Mesh.h"
#include "SkinnedMesh.h"

using namespace SWGE;
using namespace Graphics;


MeshBuffer::MeshBuffer() noexcept
	:	mIndexBuffer(nullptr),
		mVertexBuffer(nullptr)
{}

MeshBuffer::~MeshBuffer()
{
	ASSERT(mVertexBuffer == nullptr, "[MeshBuffer] vertex buffer not released!");
	ASSERT(mIndexBuffer == nullptr, "[MeshBuffer] Index buffer not released!");
}


//void MeshBuffer::Initialize(const void* verticies, uint32_t vertexsize, uint32_t vertexcount,const uint32_t* indicies, uint32_t indexcount)
//{
//	auto graphicsSystem = Graphics::GraphicsSystem::Get();																		
//	auto device = graphicsSystem->GetDevice();
//
//	mSize = vertexsize;
//	mVertexCount = vertexcount;
//	mIndexCount = indexcount;
//
//	////////////////////////////////
//	//Create and fill vertex buffer
//	D3D11_BUFFER_DESC bufferDesc = {}; // 0 initialize
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //specify the usage
//	bufferDesc.ByteWidth = vertexsize * vertexcount; // the size of vertex
//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufferDesc.CPUAccessFlags = 0; // will cpu need access to this buffer
//	bufferDesc.MiscFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA initData = {};
//	initData.pSysMem = verticies;
//	device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
//
//
//	////////////////////////////////
//	//Create and fill index buffer
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //specify the usage
//	bufferDesc.ByteWidth = sizeof(uint32_t) * indexcount; // the size of vertex
//	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	bufferDesc.CPUAccessFlags = 0; // will cpu need access to this buffer
//	bufferDesc.MiscFlags = 0;
//
//	initData.pSysMem = indicies;
//	device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
//
//}
//void MeshBuffer::Initialize(void* verticies, uint32_t vertexsize, uint32_t vertexcount)
//{
//	mSize = vertexsize;
//	mVertexCount = vertexcount;
//	auto graphicsSystem = Graphics::GraphicsSystem::Get();
//	auto device = graphicsSystem->GetDevice();
//	////////////////////////////////
//	//Create and fill vertex buffer
//	D3D11_BUFFER_DESC bufferDesc = {}; // 0 initialize
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //specify the usage
//	bufferDesc.ByteWidth = vertexsize * vertexcount; // the size of vertex
//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bufferDesc.CPUAccessFlags = 0; // will cpu need access to this buffer
//	bufferDesc.MiscFlags = 0;
//
//	D3D11_SUBRESOURCE_DATA initData = {};
//	initData.pSysMem = verticies;
//	//device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
//
//}




void MeshBuffer::Initialize(const void* vertexData, uint32_t vertexSize, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices, bool dynamic)
{
	mSize = vertexSize;
	mVertexCount = numVertices;
	mIndexCount = numIndices;
	mDynamic = dynamic;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bd.ByteWidth = vertexSize * mVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexData;

	ID3D11Device* device = GraphicsSystem::Get()->GetDevice();
	device->CreateBuffer(&bd, &initData, &mVertexBuffer);

	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(uint32_t) * mIndexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	ZeroMemory(&initData, sizeof(initData));

	initData.pSysMem = indexData;
	device->CreateBuffer(&bd, &initData, &mIndexBuffer);
}


void MeshBuffer::Initialize(const Mesh& mesh, bool dynamic)
{
	Initialize
	(
		mesh.GetVertices(),
		sizeof(Vertex),
		mesh.GetVertexCount(),
		mesh.GetIndices(),
		mesh.GetIndexCount(),
		dynamic
	);
}

void MeshBuffer::Initialize(const SkinnedMesh& skinmesh, bool dynamic)
{
	Initialize
	(
		skinmesh.GetVertices(),
		sizeof(Vertex),
		skinmesh.GetVertexCount(),
		skinmesh.GetIndices(),
		skinmesh.GetIndexCount(),
		dynamic
	);
}

void MeshBuffer::Terminate()
{
	if (mIndexBuffer)
	{
		SafeRelease(mIndexBuffer);
	}
	if (mVertexBuffer)
	{
		SafeRelease(mVertexBuffer);
	}
}
void MeshBuffer::Render() const
{
	//set primitive topology
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = mSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//Check if we are using Index buffer
	if (mIndexBuffer != nullptr)
	{
		//set index buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//Draw indexed mesh
		context->DrawIndexed(mIndexCount, 0, 0);
	}
	else
	{
		//Draw mesh
		context->Draw(mVertexCount, 0);
	}
	//mMesh ->render somthing like that


}