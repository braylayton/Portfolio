#include "Precompiled.h"
#include "GameObject.h"
#include "Component.h"

using namespace SWGE;
using namespace GameEngine;

//META_CLASS_BEGIN(GameObject)
//META_NO_FIELD
//META_CLASS_END


GameObject::GameObject()
	:mName{"GameObject"}
{

}

GameObject::~GameObject()
{

}

void GameObject::Initialize()
{
	for (auto& component : mComponents)
	{
		//component->Initialize();
	}
}

void GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		//component->Terminate();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : mComponents)
	{
		//component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	for (auto& component : mComponents)
	{
		//component->Render();
	}
}

//void GameObject::Render2D()
//{
//	for (auto& component : mComponents)
//	{
//		//component->Render2D();
//	}
//}

Component* GameObject::AddComponent(const SWGE::Core::MetaClass* metaClass)
{
	mComponents.emplace_back(static_cast<Component*>(metaClass->Create()));
	auto& newComponent = mComponents.back();
	newComponent->mGameObject = this;
	return newComponent.get();
}