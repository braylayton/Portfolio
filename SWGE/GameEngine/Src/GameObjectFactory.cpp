#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "Utility.h"

using namespace SWGE;
using namespace GameEngine;

GameObjectFactory::GameObjectFactory(GameObjectAllocator& allocator)
	: mGameObjectAllocator(allocator)
{

}

GameObject* GameObjectFactory::Create(const char* templatedFileName)
{
	GameObject* gameObject = mGameObjectAllocator.New();
	// Expression = "somthing" that evaluates to a single value of a single type

	tinyxml2::XMLDocument templateDoc;
	VERIFY(templateDoc.LoadFile(templatedFileName), "[GameObjectFactory] Failed to open template file '%s.", templatedFileName);

	const tinyxml2::XMLNode* gameObjectNode = templateDoc.FirstChild();
	if (strcmp(gameObjectNode->Value(), "GameObject") == 0)
	{
		const tinyxml2::XMLNode* componentsNode = gameObjectNode->FirstChild();
		if (strcmp(componentsNode->Value(), "Components") == 0)
		{
			const tinyxml2::XMLNode* nextComponentNode = componentsNode->FirstChild();

			while (nextComponentNode != nullptr)
			{
				const char* componentName = nextComponentNode->Value();

				const SWGE::Core::MetaClass* metaClass = SWGE::Core::MetaRegistry::FindMetaClass(componentName);
				if (metaClass == nullptr)
				{
					LOG("Class [%s] not registered with the meta system.", componentName);
				}
				else
				{
					auto newComponent = gameObject->AddComponent(metaClass);
					const tinyxml2::XMLNode* data = nextComponentNode->FirstChild();
					VERIFY(Util::XMLReader::Read(newComponent, metaClass, data), "Failed to read %s.", componentName);
				}
				nextComponentNode = nextComponentNode->NextSibling();
			}
		}
	}

	return gameObject;
}
void GameObjectFactory::Destroy(GameObject* gameObject)
{

}


//bool ead  