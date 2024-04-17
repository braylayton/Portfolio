#include "Precompiled.h"

#include "SceneNodeInc\SceneManager.h"

#include "SceneNodeInc\CameraNode.h"
#include "SceneNodeInc\ConstantBufferNode.h"
#include "SceneNodeInc\DepthMapNode.h"
#include "SceneNodeInc\LightNode.h"
#include "SceneNodeInc\MaterialNode.h"
#include "SceneNodeInc\MeshNode.h"
#include "SceneNodeInc\RasterizerStateNode.h"
#include "SceneNodeInc\RenderTargetNode.h"
#include "SceneNodeInc\SamplerNode.h"
#include "SceneNodeInc\ShaderNode.h"
#include "SceneNodeInc\TextureNode.h"
#include "SceneNodeInc\TransformNode.h"

using namespace SWGE;
using namespace Graphics;


//====================================================================================================
// Class Definitions
//====================================================================================================

SceneManager::SceneManager()
	: mpRoot(nullptr)
{
}

//----------------------------------------------------------------------------------------------------

SceneManager::~SceneManager()
{
	ASSERT(mNodes.empty(), "[SceneManager] Purge() must be called before destruction.");
}

//----------------------------------------------------------------------------------------------------

SceneNode * SWGE::Graphics::SceneManager::CreateEmptySceneNode()
{
	SceneNode* sceneNode = new SceneNode();
	mNodes.push_back(sceneNode);
	return sceneNode;
}

CameraNode* SceneManager::CreateCameraNode(const Camera& camera, bool isOrthographic, bool isLightCamera)
{
	CameraNode* newNode = new CameraNode(camera , isOrthographic, isLightCamera);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

ConstantBufferNode* SceneManager::CreateConstantBufferNode()
{
	ConstantBufferNode* newNode = new ConstantBufferNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------


DepthMapNode* SceneManager::CreateDepthMapNode()
{
	DepthMapNode* newNode = new DepthMapNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

LightNode* SceneManager::CreateLightNode(const Light& light)
{
	
	LightNode* newNode = new LightNode(light);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

MaterialNode* SceneManager::CreateMaterialNode(const Material& material)
{
	MaterialNode* newNode = new MaterialNode(material);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

MeshNode* SceneManager::CreateMeshNode()
{
	MeshNode* newNode = new MeshNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

RasterizerStateNode* SceneManager::CreateRasterizerStateNode()
{
	RasterizerStateNode* newNode = new RasterizerStateNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------
RenderTargetNode* SceneManager::CreateRenderTargetNode()
{
	RenderTargetNode* newNode = new RenderTargetNode();
	mNodes.push_back(newNode);
	return newNode;
}
//----------------------------------------------------------------------------------------------------

SamplerNode* SceneManager::CreateSamplerNode(Graphics::Sampler::Filter filter, Graphics::Sampler::AddressMode addressMode, uint32_t index)
{
	SamplerNode* newNode = new SamplerNode(filter, addressMode, index);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

ShaderNode* SceneManager::CreateShaderNode()
{
	ShaderNode* newNode = new ShaderNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TextureNode* SceneManager::CreateTextureNode()
{
	TextureNode* newNode = new TextureNode();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TransformNode* SceneManager::CreateTransformNode()
{
	TransformNode* newNode = new TransformNode(mMatrixStack);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
	return 0;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::SetRoot(SceneNode* root)
{
	mpRoot = root;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Purge()
{
	const uint32_t numNodes = mNodes.size();
	for (uint32_t i = 0; i < numNodes; ++i)
	{
		SafeDelete(mNodes[i]);
	}
	mNodes.clear();
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Update(float deltaTime)
{
	if (mpRoot != nullptr)
	{
		mpRoot->Update(deltaTime);
	}
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Render()
{
	if (mpRoot != nullptr)
	{
		mpRoot->Render();
	}
}