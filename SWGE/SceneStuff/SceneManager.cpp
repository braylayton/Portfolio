//====================================================================================================
// Filename:	SceneManager.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SceneManager.h"

#include "CameraNode.h"
#include "LightNode.h"
#include "MaterialNode.h"
#include "MeshNode.h"
#include "SamplerNode.h"
#include "ShaderNode.h"
#include "TextureNode.h"
#include "TransformNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

SceneManager::SceneManager(GraphicsSystem& gs, MatrixStack& ms)
	: mGraphicsSystem(gs)
	, mMatrixStack(ms)
	, mpRoot(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SceneManager::~SceneManager()
{
	ASSERT(mNodes.empty(), "[SceneManager] Purge() must be called before destruction.");
}

//----------------------------------------------------------------------------------------------------

CameraNode* SceneManager::CreateCameraNode()
{
	CameraNode* newNode = new CameraNode(mGraphicsSystem);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

LightNode* SceneManager::CreateLightNode()
{
	LightNode* newNode = new LightNode(mGraphicsSystem);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

MaterialNode* SceneManager::CreateMaterialNode()
{
	MaterialNode* newNode = new MaterialNode(mGraphicsSystem);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

MeshNode* SceneManager::CreateMeshNode()
{
	MeshNode* newNode = new MeshNode(mGraphicsSystem);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

SamplerNode* SceneManager::CreateSamplerNode()
{
	SamplerNode* newNode = new SamplerNode(mGraphicsSystem);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

ShaderNode* SceneManager::CreateShaderNode()
{
	ShaderNode* newNode = new ShaderNode(mGraphicsSystem);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TextureNode* SceneManager::CreateTextureNode()
{
	TextureNode* newNode = new TextureNode(mGraphicsSystem);
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

TransformNode* SceneManager::CreateTransformNode()
{
	TransformNode* newNode = new TransformNode(mGraphicsSystem, mMatrixStack);
	newNode->Initialize();
	mNodes.push_back(newNode);
	return newNode;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::SetRoot(SceneNode* root)
{
	mpRoot = root;
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Purge()
{
	const u32 numNodes = mNodes.size();
	for (u32 i = 0; i < numNodes; ++i)
	{
		SafeDelete(mNodes[i]);
	}
	mNodes.clear();
}

//----------------------------------------------------------------------------------------------------

void SceneManager::Update(f32 deltaTime)
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