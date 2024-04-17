#include "Precompiled.h"
#include "SceneNodeInc\DepthMapNode.h"

using namespace SWGE;
using namespace Graphics;

DepthMapNode::DepthMapNode()
	: SceneNode("DepthMapNode")
{
}

DepthMapNode::~DepthMapNode()
{
	mDepthMap.Terminate();
}

void DepthMapNode::Initialize(uint32_t width, uint32_t height)
{
	mDepthMap.Initialize(width, height);
}

void DepthMapNode::OnRender()
{
	mDepthMap.BeginRender();
}
void DepthMapNode::OnPostRender()
{
	mDepthMap.EndRender();
}