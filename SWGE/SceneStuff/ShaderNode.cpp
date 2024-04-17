//====================================================================================================
// Filename:	ShaderNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "ShaderNode.h"

#include "PixelShader.h"
#include "VertexShader.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

ShaderNode::ShaderNode(GraphicsSystem& gs)
	: SceneNode(gs)
	, mpVertexShader(nullptr)
	, mpPixelShader(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

ShaderNode::~ShaderNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void ShaderNode::OnRender()
{
	if (mpVertexShader != nullptr)
	{
		mpVertexShader->Bind(mGraphicsSystem);
	}
	if (mpPixelShader != nullptr)
	{
		mpPixelShader->Bind(mGraphicsSystem);
	}
}