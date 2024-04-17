#include "Precompiled.h"
#include "SceneNodeInc\RenderTargetNode.h"

using namespace SWGE;
using namespace Graphics;

RenderTargetNode::RenderTargetNode()
	: SceneNode("RenderTargetNode")
{
}
 RenderTargetNode::~RenderTargetNode()
{
	 renderTarget.Terminate();
}

void RenderTargetNode::Initialize(uint32_t width, uint32_t height, ColorFormat format)
{
	renderTarget.Initialize(width, height, format);
}

void RenderTargetNode::OnRender()
{
	renderTarget.BeginRender();
}

void RenderTargetNode::OnPostRender()
{
	renderTarget.EndRender();
}