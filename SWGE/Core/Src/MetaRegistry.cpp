#include "Precompiled.h"
#include "MetaRegistry.h"
#include "MetaClass.h"

using namespace SWGE;
using namespace Core;
using namespace MetaRegistry;

namespace
{
	using MetaClassMap = std::map<std::string, const MetaClass*>;
	inline MetaClassMap& GetRegistry()
	{
		static MetaClassMap sMetaClassMap;
		return sMetaClassMap;
	}
}

void MetaRegistry::Register(const MetaClass* metaClass)
{
	GetRegistry().emplace(metaClass->GetName(), metaClass);
}

const MetaClass* MetaRegistry::FindMetaClass(const char* className)
{
	MetaClassMap::const_iterator iter = GetRegistry().find(className);
	ASSERT(iter != GetRegistry().end(), "[MetaRegistry] Meta Class for %s not found.");
	return iter->second;
}
