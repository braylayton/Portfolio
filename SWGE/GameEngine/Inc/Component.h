#pragma once

#include "Core/Inc/Meta.h"

namespace SWGE {
namespace GameEngine {

class GameObject;

class Component
{
public:
	//META_CLASS_DECLARE;

	Component();
	virtual ~Component();

	virtual void Initialize() {}
	virtual void Terminate() {}

	virtual void Update() {}
	virtual void Render() {}
	//virtual void Render2D() {}
	
	GameObject& GetOwner() { return *mGameObject; }
	const GameObject& GetOwner() const { return *mGameObject; }

private:
	friend class GameObject;

	GameObject* mGameObject;



}; 

}
}