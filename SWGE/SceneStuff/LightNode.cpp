//====================================================================================================
// Filename:	LightNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "LightNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

LightNode::LightNode(GraphicsSystem& gs)
	: SceneNode(gs)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

LightNode::~LightNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void LightNode::Initialize()
{
	mConstantBuffer.Initialize(mGraphicsSystem);
}

//----------------------------------------------------------------------------------------------------

void LightNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void LightNode::OnRender()
{
	const XMFLOAT4& direction = mLight.GetDirection();
	const XMFLOAT4& ambient = mLight.GetAmbient();
	const XMFLOAT4& diffuse = mLight.GetDiffuse();
	const XMFLOAT4& specular = mLight.GetSpecular();

	ConstantBuffer constants;
	constants.direction = XMVectorSet(direction.x, direction.y, direction.z, direction.w);
	constants.ambient = XMVectorSet(ambient.x, ambient.y, ambient.z, ambient.w);
	constants.diffuse = XMVectorSet(diffuse.x, diffuse.y, diffuse.z, diffuse.w);
	constants.specular = XMVectorSet(specular.x, specular.y, specular.z, specular.w);
	mConstantBuffer.Set(mGraphicsSystem, constants);
	
	mConstantBuffer.BindVS(mGraphicsSystem, 1);
	mConstantBuffer.BindPS(mGraphicsSystem, 1);
}