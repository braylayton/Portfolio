#include "Precompiled.h"
#include "Component.h"

using namespace SWGE;
using namespace GameEngine;

//META_CLASS_BEGIN(Component)
//template<> const SWGE::Core::MetaType* GetMetaType<Component>()
//{
//return ClassType::StaticGetMetaClass();
//}
//const SWGE::Core::MetaClass* Component::StaticGetMetaClass()
//{
//using LocalType = Component;
//const char* const className = #Component;
//const SWGE::Core::MetaClass* parentMetaClass = nullptr;
	//META_FIELD_BEGIN
	//META_NO_FIELD
	//META_FIELD_END
//		static const SWGE::Core::MetaField* fields = nullptr; \
//		static const size_t numFields = 0;
//
//META_CLASS_END
//static const SWGE::Core::MetaClass sMetaClass(className, sizeof(Component), \
//	[] { return new Component(); }, \
//	[](void* data) { delete static_cast<Component*>(data); }, \
//	parentMetaClass, fields, numFields); \
//	return &sMetaClass; \
//}

Component::Component()
	: mGameObject{nullptr}
{

}

Component::~Component()
{

}