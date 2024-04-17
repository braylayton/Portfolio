#pragma once


namespace SWGE {
namespace Core {

class MetaType;

template<class DataType>
inline const MetaType* GetMetaType()
{
	static_assert(sizeof(DataType) == -1, "Cannot deduce Type");
}

template <class ClassType, class DataType>
inline const MetaType* GetMetaType(DataType ClassType::* field)
{
	return GetMetaType<DataType>();
}

template<class ClassType, class DataType>
inline size_t GetFieldOffset(DataType ClassType::* field)
{
	return (size_t)(void*)&(((ClassType*)nullptr)->*field);
}

template <class BaseType, class DerivedType>
inline DerivedType* DynamicCast(BaseType* ptr)
{
	if (ptr->GetMetaClass() != DerivedType::StaticGetMetaClass())
	{
		return nullptr;
	}
	else
	{
		return static_cast<DerivedType*>(ptr);
	}
}

// Meta Type has to constexpr
/*
template <class BaseType, class DerivedType>
inline bool IsBaseOf()
{

	auto parent = DerivedType::StaticGetMetaClass()->GetParent()
	while(parent != nullptr)
	{
		if (parent == BaseType::StaticGetMetaClass())
		{
			return true;
		}
		else
		{
			parent = parent->GetParent();
		}
	}
	return false;
}
*/

//template<class BaseType, class DerivedType>
//DerivedType* DynamicCast(BaseType* ptr)
//{
//
//}


/*

template<class DataType>
const MetaType* DeduceType()
{
	if constexpr(is_equal_to_v<DataType, int>())
	{
		// do int stuff
	}
	else
	{
		static_assert()
	}
}

*/



}
}
