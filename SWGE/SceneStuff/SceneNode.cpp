//====================================================================================================
// Filename:	SceneNode.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SceneNode.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

SceneNode::SceneNode(GraphicsSystem& gs)
	: mGraphicsSystem(gs)
	, mpParent(nullptr)
	, mName("Unknown")
	, mId(-1)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SceneNode::~SceneNode()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

bool SceneNode::AddChild(SceneNode* child)
{
	// Add child to list and set self to be parent
	mChildren.push_back(child);
	child->mpParent = this;
	return true;
}

//--------------------------------------------------------w--------------------------------------------

bool SceneNode::RemoveChild(const char* name)
{
	const u32 numChildren = mChildren.size();
	for (u32 i = 0; i < numChildren; ++i)
	{
		if (mChildren[i]->mName == name)
		{
			mChildren[i] = mChildren[numChildren - 1];
			mChildren.pop_back();
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

bool SceneNode::RemoveChild(u32 id)
{
	const u32 numChildren = mChildren.size();
	for (u32 i = 0; i < numChildren; ++i)
	{
		if (mChildren[i]->mId == id)
		{
			mChildren[i] = mChildren[numChildren - 1];
			mChildren.pop_back();
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

void SceneNode::Update(f32 deltaTime)
{
	OnUpdate(deltaTime);

	for (SceneNode* child : mChildren)
	{
		child->Update(deltaTime);
	}
}

//----------------------------------------------------------------------------------------------------

void SceneNode::Render()
{
	OnPreRender();
	OnRender();
	
	for (SceneNode* child : mChildren)
	{
		child->Render();
	}

	OnPostRender();
}