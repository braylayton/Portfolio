//====================================================================================================
// Filename:	TransformNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "TransformNode.h"

#include "MatrixStack.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

TransformNode::TransformNode(GraphicsSystem& gs, MatrixStack& ms)
	: SceneNode(gs)
	, mMatrixStack(ms)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

TransformNode::~TransformNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::Initialize()
{
	mConstantBuffer.Initialize(mGraphicsSystem);
}

//----------------------------------------------------------------------------------------------------

void TransformNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnUpdate(f32 deltaTime)
{
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPreRender()
{
	mMatrixStack.PushMatrix(mTransform.GetTransform());
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnRender()
{
	ConstantBuffer constants;
	constants.matWorld = XMLoadFloat4x4(&mMatrixStack.GetMatrixTranspose());
	mConstantBuffer.Set(mGraphicsSystem, constants);
	
	mConstantBuffer.BindVS(mGraphicsSystem, 3);
	mConstantBuffer.BindPS(mGraphicsSystem, 3);
}

//----------------------------------------------------------------------------------------------------

void TransformNode::OnPostRender()
{
	mMatrixStack.PopMatrix();
}