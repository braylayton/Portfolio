#include "Precompiled.h"
#include "SceneNodeInc\ShaderNode.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsSystem.h"
using namespace SWGE;
using namespace Graphics;

ShaderNode::ShaderNode()
	: SceneNode("ShaderNode")
	, mVertexShader(nullptr)
	, mPixelShader(nullptr)
{
}



ShaderNode::~ShaderNode()
{
	// Empty
}


void ShaderNode::OnRender()
{
	if (mVertexShader != nullptr)
	{
		mVertexShader->Bind();
	}
	if (mPixelShader != nullptr)
	{
		mPixelShader->Bind();
	}
	else
	{
		Graphics::GraphicsSystem::Get()->GetContext()->PSSetShader(nullptr, nullptr, 0);
	}
}