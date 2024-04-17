#ifndef INCLUDED_GAMEENGINE_GAMEOBJECT_H
#define INCLUDED_GAMEENGINE_GAMEOBJECT_H

#include "Common.h"

namespace SWGE{
namespace GameEngine {


class Component;
class GameObject;
class World;

using GameObjectHandle = Core::Handle<GameObject>;
using GameObjectHandlePool = Core::HandlePool<GameObject>;
using GameObjectAllocator = Core::TypedAllocator<GameObject>;

class GameObject
{
public:
	//META_CLASS_DECLARE;

	GameObject();
	~GameObject();

	void Initialize();
	void Terminate();

	void Update(float deltaTime);
	void Render();
	//void Render2D();

	Component* AddComponent(const SWGE::Core::MetaClass* metaClass);

	template <typename T>
	typename std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent();
		//AddComponent(std::unique_ptr<Component> component);

	Component* GetComponentAt(size_t index);
	size_t GetComponentCount() const { return mComponents.size(); }
 
	const std::string& GetName() const { return mName; }
	const GameObjectHandle GetHandle() const { return mHandle; }
	

private:
	friend class World;
	using Components = std::vector<std::unique_ptr<Component>>;

	World* mWorld;
	std::string mName;
	GameObjectHandle mHandle;
	Components mComponents;
};


template <typename T>
typename std::enable_if_t<std::is_base_of_v<Component, T>, T*> AddComponent(std::unique_ptr<Component> component)
{
	auto& newComponet = mComponents.emplace_back(std::make_unique<T>());
	newComponet->mGameObject = this;
	return static_cast<T*>(newComponent.get());

}



}
}



#endif // !INCLUDED_ENGINE_GAMEOBJECT_H

/*
 NOTES:
template <typename T>
T* GameObject::GetComponent()
{
	T* result = nullptr;
	for (auto& component : mComponents)
	{
		// if this is the right component
		T* casted = dynamic_cast<T*>(component.get());
		if (casted)
		{
			result = component.get();
		}
	}
	return result;
}
*/

// dynamic_cast Runtime
// static_cast Compile time 
// however static cast cannot tell if a car pointer has a tesla pointer...? whhile dynamic can 
//RTTI is acronymn RunTimeTypeInformation

//Explcit Template Specialization
//template<>
//For special function versions 