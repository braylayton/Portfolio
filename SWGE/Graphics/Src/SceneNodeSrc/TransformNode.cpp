#include "Precompiled.h"
#include "SceneNodeInc\TransformNode.h"
#include "Camera.h"

using namespace SWGE;
using namespace Graphics;


TransformNode::TransformNode(MatrixStack& ms)
	: SceneNode("TransformNode")
	, mMatrixStack(ms)
{
}

TransformNode::~TransformNode()
{
	Terminate();
}


void TransformNode::Initialize()
{
	mConstantBuffer.Initialize();
}


void TransformNode::Terminate()
{
	mConstantBuffer.Terminate();
}


void TransformNode::OnUpdate(float deltaTime)
{

}


void TransformNode::OnPreRender()
{
	mMatrixStack.PushMatrix(mTransform.GetTransform());
}


void TransformNode::OnRender()
{
	ConstantBuffer constants;
	const auto matWorld = mMatrixStack.GetMatrixTranspose();
	constants.matWorld = matWorld;

	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(3);
	mConstantBuffer.BindPS(3);
}


void TransformNode::OnPostRender()
{
	mMatrixStack.PopMatrix();
}