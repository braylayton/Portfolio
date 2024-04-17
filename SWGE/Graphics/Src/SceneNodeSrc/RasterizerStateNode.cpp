#include "Precompiled.h"
#include "SceneNodeInc\RasterizerStateNode.h"

using namespace SWGE;
using namespace Graphics;

RasterizerStateNode::RasterizerStateNode()
	:SceneNode("RasterizerStateNode")
{
}

RasterizerStateNode::~RasterizerStateNode()
{
	mRasterizerState.Terminate();
}

void RasterizerStateNode::Initialize(CullMode cullMode, FillMode fillMode)
{
	mRasterizerState.Initialize(cullMode, fillMode);
}
void  RasterizerStateNode::OnRender() 
{
	mRasterizerState.Set();
}
void  RasterizerStateNode::OnPostRender()
{
	mRasterizerState.Clear();
}