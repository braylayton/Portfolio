//====================================================================================================
// Filename:	MaterialNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MaterialNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

MaterialNode::MaterialNode(GraphicsSystem& gs)
	: SceneNode(gs)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

MaterialNode::~MaterialNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::Initialize()
{
	mConstantBuffer.Initialize(mGraphicsSystem);
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void MaterialNode::OnRender()
{
	const XMFLOAT4& ambient = mMaterial.GetAmbient();
	const XMFLOAT4& diffuse = mMaterial.GetDiffuse();
	const XMFLOAT4& specular = mMaterial.GetSpecular();
	const XMFLOAT4& emissive = mMaterial.GetEmissive();

	ConstantBuffer constants;
	constants.ambient = XMVectorSet(ambient.x, ambient.y, ambient.z, ambient.w);
	constants.diffuse = XMVectorSet(diffuse.x, diffuse.y, diffuse.z, diffuse.w);
	constants.specular = XMVectorSet(specular.x, specular.y, specular.z, specular.w);
	constants.emissive = XMVectorSet(emissive.x, emissive.y, emissive.z, emissive.w);
	constants.power = mMaterial.GetPower();
	mConstantBuffer.Set(mGraphicsSystem, constants);
	
	mConstantBuffer.BindVS(mGraphicsSystem, 2);
	mConstantBuffer.BindPS(mGraphicsSystem, 2);
}