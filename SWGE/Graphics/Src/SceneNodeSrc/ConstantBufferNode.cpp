#include "Precompiled.h"
#include "SceneNodeInc\ConstantBufferNode.h"

using namespace SWGE;
using namespace Graphics;

namespace
{
uint32_t GetPaddedSize(uint32_t size)
{
	const uint32_t typeSize = size;
	const uint32_t bufferSize = (typeSize % 16) ? ((typeSize / 16) + 1) * 16 : typeSize;
	return bufferSize;
}
}

ConstantBufferNode::ConstantBufferNode()
{
}

ConstantBufferNode::~ConstantBufferNode()
{
	mConstantBuffer.Terminate();
}

void ConstantBufferNode::Initialize(uint32_t bufferSize, const ShaderStage shaderStages, const uint32_t slot, const void* initData)
{
	mConstantBuffer.Initialize(GetPaddedSize(bufferSize), initData);
	mShaderStages = shaderStages;
	mSlot = slot;
}

void ConstantBufferNode::OnRender()
{
	if ((mShaderStages & ShaderStage::Vertex) != ShaderStage::None) 
	{
		mConstantBuffer.BindVS(mSlot);
	}
	if ((mShaderStages & ShaderStage::Geometry) != ShaderStage::None)
	{
		mConstantBuffer.BindGS(mSlot);
	}
	if ((mShaderStages & ShaderStage::Pixel) != ShaderStage::None)
	{
		mConstantBuffer.BindPS(mSlot);
	}
	if ((mShaderStages & ShaderStage::Compute) != ShaderStage::None)
	{
		mConstantBuffer.BindCS(mSlot);
	}
}
void ConstantBufferNode::OnPostRender()
{
}

void ConstantBufferNode::Set(const void* data) const
{
	mConstantBuffer.Set(data);
}
