//====================================================================================================
// Filename:	SamplerNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SamplerNode.h"

#include "GraphicsSystem.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

SamplerNode::SamplerNode(GraphicsSystem& gs)
	: SceneNode(gs)
	, mpSampler(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SamplerNode::~SamplerNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::Initialize()
{
	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof(sampDesc) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	mGraphicsSystem.GetDevice()->CreateSamplerState(&sampDesc, &mpSampler);
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::Terminate()
{
	SafeRelease(mpSampler);
}

//----------------------------------------------------------------------------------------------------

void SamplerNode::OnRender()
{
	mGraphicsSystem.GetContext()->PSSetSamplers(0, 1, &mpSampler);
}