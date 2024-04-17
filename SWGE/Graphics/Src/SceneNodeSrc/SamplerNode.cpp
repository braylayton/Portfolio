#include "Precompiled.h"
#include "SceneNodeInc\SamplerNode.h"
#include "GraphicsSystem.h"

using namespace SWGE;
using namespace Graphics;


SamplerNode::SamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode addressMode, uint32_t index)
	: SceneNode("SamplerNode")
	, mFilter(filter)
	, mAddressMode(addressMode)
	, mIndex(index)
{
}

SamplerNode::~SamplerNode()
{
	mSampler.Terminate();
}

void SamplerNode::Initialize()
{
	mSampler.Initialize(mFilter, mAddressMode);
	// Create the sample state
	/*
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11Device* device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = device->CreateSamplerState(&sampDesc, &mSampler);
	ASSERT(SUCCEEDED(hr), "[Sampler] Failed to create sampler state.");
	*/
}

void SamplerNode::OnRender()
{
	mSampler.BindVS(mIndex);
	mSampler.BindGS(mIndex);
	mSampler.BindPS(mIndex);
}

void SamplerNode::Terminate()
{
	mSampler.Terminate();
}