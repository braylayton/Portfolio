#pragma once

#include "MetaClass.h"
#include "MetaField.h"
#include "MetaRegistry.h"
#include "MetaType.h"
#include "MetaUtil.h"

// stop compiler from generating stuff
#define META_TYPE_DECLARE(Type)\
template <> const SWGE::Core::MetaType* SWGE::Core::GetMetaType<Type>();

#define META_TYPE_DEFINE(Type, Name)\
	template <> const SWGE::Core::MetaType* SWGE::Core::GetMetaType<Type>()\
	{\
		static SWGE::Core::MetaType sMetaType(\
			Name,\
			SWGE::Core::MetaType::Category::Primitive,\
			sizeof(Type),\
			[]{ return new Type; },\
			[](void* data){ delete static_cast<Type*>(data); }\
			);\
		return &sMetaType;\
	}

#define META_CLASS_DECLARE\
	static const SWGE::Core::MetaClass* StaticGetMetaClass();\
	virtual const SWGE::Core::MetaClass* GetMetaClass() const {return StaticGetMetaClass();}

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	template<> const SWGE::Core::MetaType* GetMetaType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const SWGE::Core::MetaClass* ClassType::StaticGetMetaClass()\
	{\
		using LocalType = ClassType;\
		const char* const className = #ClassType;

#define META_CLASS_BEGIN_DERIVED(ClassType, ParentType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const SWGE::Core::MetaClass* parentMetaClass = ParentType::StaticGetMetaClass();

#define META_CLASS_BEGIN(ClassType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const SWGE::Core::MetaClass* parentMetaClass = nullptr;


#define META_FIELD_BEGIN\
	static const SWGE::Core::MetaField fields[] = {
#define META_FIELD(Var, Name)\
		SWGE::Core::MetaField(Name, GetMetaType(&LocalType::Var), GetFieldOffset(&LocalType::Var));,

#define META_FIELD_END\
	};\
	static const size_t numFields = std::size(fields);

#define META_NO_FIELD\
	static const SWGE::Core::MetaField* fields = nullptr;\
	static const size_t numFields = 0;

#define META_CLASS_END\
	static const SWGE::Core::MetaClass sMetaClass(className, sizeof(Class),\
	[] { return new Class(); },\
	[] (void* data ){ delete static_cast<Class*>(data); },\
	parentMetaClass, fields, numFields);\
	return &sMetaClass;\
	}


