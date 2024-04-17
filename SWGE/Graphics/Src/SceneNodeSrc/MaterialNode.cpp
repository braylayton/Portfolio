#include "Precompiled.h"
#include "SceneNodeInc\MaterialNode.h"

using namespace SWGE;
using namespace Graphics;

MaterialNode::MaterialNode(const Material& material)
	: SceneNode("MaterialNode")
	, mMaterial(material)
{
}

MaterialNode::~MaterialNode()
{
	Terminate();
}

void MaterialNode::Initialize()
{
	mConstantBuffer.Initialize();
}

void MaterialNode::Terminate()
{
	mConstantBuffer.Terminate();
}

void MaterialNode::OnRender()
{ 
	//ConstantBuffer constants;
	//constants.ambient = mMaterial.GetAmbient();
	//constants.diffuse = mMaterial.GetDiffuse();
	//constants.specular = mMaterial.GetSpecular();
	//constants.emissive = mMaterial.GetEmissive();
	//constants.power = mMaterial.GetPower();
	//constants.displacementFactor = mMaterial.GetDisplacementFactor();

	mConstantBuffer.Set(mMaterial);

	mConstantBuffer.BindVS(2);
	mConstantBuffer.BindPS(2);
}