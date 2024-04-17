#include "Precompiled.h"
#include "SceneNodeInc\LightNode.h"

using namespace SWGE;
using namespace Graphics;

LightNode::LightNode(const Light& light)
	: SceneNode("LightNode")
	, mLight(light)
{
}

LightNode::~LightNode()
{
	Terminate();
}

void LightNode::Initialize()
{
	mConstantBuffer.Initialize();
}

void LightNode::Terminate()
{
	mConstantBuffer.Terminate();
}

void LightNode::OnRender()
{
	ConstantBuffer constants;
	constants.direction = mLight.GetDirection();
	constants.ambient = mLight.GetAmbient();
	constants.diffuse = mLight.GetDiffuse();
	constants.specular = mLight.GetSpecular();
	mConstantBuffer.Set(constants);

	mConstantBuffer.BindVS(1);
	mConstantBuffer.BindPS(1);
}