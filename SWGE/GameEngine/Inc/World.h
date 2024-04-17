#pragma once

#include "GameEngine\Inc\GameObjectFactory.h"

namespace SWGE{
namespace GameEngine {

class World
{
public:
	void Initialize(uint32_t capacity);
	void Terminate();

	void LoadLevel(const char* levelFileName);
	GameObjectHandle Create(const char* templateFileName, const char* name);
	//GameObjectHandle Find(const char* name);

	void Destroy(GameObjectHandle handle);

	void Update(float deltaTime);
	void Render();
private:
	void DestroyInternal(GameObject* gameObject);
	void ProcessDestroyList();

	using GameObjectList = std::vector<GameObject*>;
	
	std::unique_ptr<GameObjectAllocator> mGameObjectAllocator;
	std::unique_ptr<GameObjectHandlePool> mGameObjectHandlePool;
	std::unique_ptr<GameObjectFactory> mGameObjectFactory;

	GameObjectList mUpdateList;
	GameObjectList mDestroyList;
	bool mInitialized{ false };
	bool mUpdating{ false };
};


}
}

