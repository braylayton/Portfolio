//====================================================================================================
// Filename:	CameraNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "CameraNode.h"

#include "Camera.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CameraNode::CameraNode(GraphicsSystem& gs)
	: SceneNode(gs)
	, mpCamera(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CameraNode::~CameraNode()
{
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Initialize()
{
	mConstantBuffer.Initialize(mGraphicsSystem);
}

//----------------------------------------------------------------------------------------------------

void CameraNode::Terminate()
{
	mConstantBuffer.Terminate();
}

//----------------------------------------------------------------------------------------------------

void CameraNode::OnUpdate(f32 deltaTime)
{
}

//----------------------------------------------------------------------------------------------------

void CameraNode::OnRender()
{
	ConstantBuffer constants;
	constants.matView = XMMatrixTranspose(mpCamera->GetViewMatrix());
	constants.matProjection = XMMatrixTranspose(mpCamera->GetProjectionMatrix());
	constants.viewPosition = XMLoadFloat3(&mpCamera->GetPosition());
	mConstantBuffer.Set(mGraphicsSystem, constants);
	
	mConstantBuffer.BindVS(mGraphicsSystem, 0);
	mConstantBuffer.BindPS(mGraphicsSystem, 0);
}