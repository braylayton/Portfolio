#ifndef INCLUDED_CORE_TYPEDALLOCATOR_H
#define INCLUDED_CORE_TYPEDALLOCATOR_H

#include "BlockAllocator.h"

namespace SWGE {
namespace Core {

template<class DataType>
class TypedAllocator : private BlockAllocator
{
public:
	TypedAllocator(uint32_t capacity)
		: BlockAllocator(sizeof(DataType), capacity)
	{
	}

	// Variadic Template Arguments 
	template<class... Args>
	DataType* New(Args&&... args);

	void Delete(DataType* ptr);
};

template<class DataType>
template<class... Args>
DataType* TypedAllocator<DataType>::New(Args&&... args)
{
	DataType* instance = static_cast<DataType*>(Allocate());
	if (instance)
	{
		// Perfect Forwarding
		new (instance) DataType(std::forward<Args>(args)...); 
	}
	return instance;
}

template<class DataType>
void TypedAllocator<DataType>::Delete(DataType* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	ptr->~T();
	Free(ptr);
}

}
}


// Notes Perfect Forwading within Make_Unique
//template<class _Ty,
//	class... _Types,
//	enable_if_t<!is_array_v<_Ty>, int> = 0>
//	_NODISCARD inline unique_ptr<_Ty> make_unique(_Types&&... _Args)
//{	// make a unique_ptr
//	return (unique_ptr<_Ty>(new _Ty(_STD forward<_Types>(_Args)...)));
//}

#endif // !1
