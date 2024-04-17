#pragma once
#include "GameObject.h"
#include <External/TinyXml2/Inc/tinyxml2.h>

namespace SWGE{
namespace GameEngine{

class GameObjectFactory
{
public:
	GameObjectFactory(GameObjectAllocator& allocator);

	GameObject* Create(const char* templatedFileName);
	void Destroy(GameObject* gameObject);
private:
	GameObjectAllocator& mGameObjectAllocator;
};

}
}

