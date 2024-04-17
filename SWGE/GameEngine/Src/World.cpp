#include "Precompiled.h"
#include "World.h"

using namespace SWGE;
using namespace GameEngine;

void World::Initialize(uint32_t capacity)
{
	ASSERT(!mInitialized, "[World] World already initialized.");

	mGameObjectAllocator = std::make_unique<GameObjectAllocator>(capacity);
	mGameObjectHandlePool = std::make_unique<GameObjectHandlePool>(capacity);
	mGameObjectFactory = std::make_unique<GameObjectFactory>(*mGameObjectAllocator);

	mInitialized = true;
}

void World::Terminate()
{
	if (!mInitialized)
	{
		return;
	}

	ASSERT(!mUpdating, "[World] cannot terminate world during update.");

	//Destroy all active objects
	mUpdating = true;
	std::for_each(mUpdateList.begin(), mUpdateList.end(), [this](GameObject* gameObject)
	{
		Destroy(gameObject->GetHandle());
	});
	mUpdating = false;
	mUpdateList.clear();

	// Now destroy everything
	ProcessDestroyList();

	mGameObjectFactory.reset();
	mGameObjectHandlePool.reset();
	mGameObjectAllocator.reset();

	mInitialized = false;
}

GameObjectHandle World::Create(const char* templateFileName, const char* name)
{
	auto gameObject = mGameObjectFactory->Create(templateFileName);
	ASSERT(gameObject != nullptr, "[World] Failed to create game object from template %s", templateFileName);

	// Register with the Handle Pool
	auto handle = mGameObjectHandlePool->Register(gameObject);

	// Initialize the game object
	gameObject->mWorld = this;
	gameObject->mHandle = handle; 
	gameObject->mName = name;
	gameObject->Initialize();

	// Add game object to the update list
	mUpdateList.push_back(gameObject);

	return handle;

}

void World::LoadLevel(const char* levelFileName)
{
	//read an xml file
	const char* nodeName;
	const char* templateFileName;
	tinyxml2::XMLDocument doc;
	VERIFY(doc.LoadFile(levelFileName), "[GameObjectFactory] Failed to open template file '%s.", levelFileName);
	
	if(strcmp(doc.FirstChild()->Value(), "GameObjects") == 0)
	{
		const tinyxml2::XMLNode* gameObjectNode = doc.FirstChild()->FirstChild();
		while (strcmp(gameObjectNode->Value(), "GameObject") == 0)
		{
			const tinyxml2::XMLNode* nameNode = gameObjectNode->FirstChild();
			VERIFY(nameNode != nullptr, "nameNode = nullptr.");
			if (strcmp(nameNode->Value(), "Name") == 0)
			{
				nodeName = nameNode->FirstChild()->Value();
			}
			const tinyxml2::XMLNode* templateNode = nameNode->NextSibling();
			VERIFY(templateNode != nullptr, "templateNode = nullptr.");
			if (strcmp(templateNode->Value(), "Template"))
			{
				templateFileName = templateNode->FirstChild()->Value();
			}
			Create(templateFileName, nodeName);
			const tinyxml2::XMLNode* overideVarNode = templateNode->NextSibling();
			VERIFY(overideVarNode != nullptr, "overideVarNode = nullptr.");
			if (strcmp(overideVarNode->Value(), "OverideComponent"))
			{
				// Find Name

				// store variables


			}



		}
		
		

	}
	



}
//GameObjectHandle World::Find(const char* name)
//{
//	
//}

void World::Destroy(GameObjectHandle handle)
{
	// If handle is invalid, nothing to do so just exit
	if (!handle.IsValid())
	{
		return;
	}
	// Cache the pointer and unregister with the handle pool
	GameObject* gameObject = handle.Get();
	mGameObjectHandlePool->Unregister(handle);

	// Check if we can destroy it now
	if (!mUpdating)
	{
		DestroyInternal(gameObject);
	}
	else
	{
		mDestroyList.push_back(gameObject);
	}

}

void World::Update(float deltaTime)
{
	ASSERT(!mUpdating, "[World] Already updating the world.");
	
	//Lock the update list
	mUpdating = true;

	//Re-compute size in case new objects are added to the update
	//list during iteration.
	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		GameObject* gameObject = mUpdateList[i];
		if (gameObject->GetHandle().IsValid())
		{
			gameObject->Update(deltaTime);
		}
	}

	mUpdating = false;

	// Now we can safel destroy objects
	ProcessDestroyList();
}
void World::Render()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}

void World::DestroyInternal(GameObject* gameObject)
{
	ASSERT(!mUpdating, "[World] Cannot destroy game objects during update.");

	// If pointer is invalid, nothing to do so just exit
	if (gameObject == nullptr)
	{
		return;
	}

	// First remove it from the update list
	auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);
	if (iter != mUpdateList.end())
	{
		mUpdateList.erase(iter);
	}

	// Terminate the game object
	gameObject->Terminate();

	// Next destroy the game object
	mGameObjectFactory->Destroy(gameObject);

}

void World::ProcessDestroyList()
{
	for (auto gameObject : mDestroyList)
	{
		DestroyInternal(gameObject);
	}
	mDestroyList.clear();
}