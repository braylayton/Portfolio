#include "Precompiled.h"
#include "SceneNodeInc\SceneNode.h"

using namespace SWGE;
using namespace Graphics;

SceneNode::SceneNode()
	: mParent(nullptr)
	, mName("Unknown")
	, mId(-1)
{
	
}

SWGE::Graphics::SceneNode::SceneNode(const char * name)
	: mParent(nullptr)
	, mName(name)
	, mId(-1)
{
}

SceneNode::~SceneNode()
{

}

bool SceneNode::AddChild(SceneNode* child)
{
	mChildren.push_back(child);
	child->mParent = this;
	return true;
}
bool SceneNode::RemoveChild(const char* name)
{
	const uint32_t numChildren = mChildren.size();
	for (uint32_t i = 0; i < mChildren.size(); ++i)
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
bool SceneNode::RemoveChild(uint32_t id)
{
	const uint32_t numChildren = mChildren.size();
	for (uint32_t i = 0; i < numChildren; ++i)
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
void SceneNode::Update(float deltaTime)
{
	OnUpdate(deltaTime);

	for (SceneNode* child : mChildren)
	{
		child->Update(deltaTime);
	}
}
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