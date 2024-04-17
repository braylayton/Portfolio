#include "Precompiled.h"
#include "MetaType.h"

using namespace SWGE;
using namespace Core;

MetaType::MetaType(const char* const name, Category category, size_t size, CreateFunc create, DestroyFunc destroy)
	: mName(name)
	, mCategory(category)
	, mId(std::hash<std::string>()(name))
	, mSize(size)
	, mCreate(std::move(create))
	, mDestroy(std::move(destroy))
{
}

//MetaType sIntType("int", MetaType::Category::Primitive, sizeof(int));