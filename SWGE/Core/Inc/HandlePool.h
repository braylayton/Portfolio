#pragma once

#include "Common.h"
#include "Handle.h"

namespace SWGE {
namespace Core {

//template <class DataType>
//class Handle;

template <class DataType>
class HandlePool
{
public:
	using HandleType = Handle<DataType>;
	HandlePool(uint32_t capacity);
	~HandlePool();

	HandleType Register(DataType* instance);
	void Unregister(HandleType handle);


	bool IsValid(HandleType handle) const;
	DataType* Get(HandleType handle) const;

private:
	struct Entry
	{
		DataType* instance = nullptr;
		uint32_t generation = 0;
	};

	std::vector<Entry> mEntries;
	std::vector<uint32_t> mFreeSlots;
};

template <typename DataType>
HandlePool<DataType>::HandlePool(uint32_t capacity)
{
	ASSERT(capacity > 0, "[HandlePool] Invalid Capacity");
	mEntries.resize(capacity + 1);
	mFreeSlots.reserve(capacity);
	for (size_t i = capacity; i > 0; i--)
	{
		mFreeSlots.push_back(i);
	}

	//Register itself with the handle type
	ASSERT(HandleType::sPool == nullptr, "[HandlePool] Cannot have more than one pool for the same type");
	HandleType::sPool = this;
}

template <typename DataType>
HandlePool<DataType>::~HandlePool()
{
	//check that all handles are freed
	ASSERT(mFreeSlots.size() == mFreeSlots.capacity(), "[HandlePool] There are still registerd slots!");

	ASSERT(HandleType::sPool == this, "[HandlePool] Somthing is wrong. ");
	HandleType::sPool = nullptr;
}

template <typename DataType>
typename HandlePool<DataType>::HandleType HandlePool<DataType>::Register(DataType* instance)
{
	ASSERT(instance != nullptr, "[HandlePool] Invalid instance.");
	ASSERT(!mFreeSlots.empty(), "[HandlePool] No  more free slots available");

	//Draw the next freeslot 
	uint32_t slot = mFreeSlots.back();
	mFreeSlots.pop_back();

	//Register the instance
	mEntries[slot].instance = instance;

	// Return a handle to the entry 
	HandleType handle;
	handle.mIndex = slot;
	handle.mGeneration = mEntries[slot].generation;
	return handle;
}

template <typename DataType>
void HandlePool<DataType>::Unregister(HandleType handle)
{
	if (!IsValid(handle))
	{
		return;
	}

	// Increment generation to invalidate all existing handles
	mEntries[handle.mIndex].generation;

	//recycle the slot
	mFreeSlots.push_back(handle.mIndex);
}


template <typename DataType>
bool HandlePool<DataType>::IsValid(HandleType handle) const
{
	return handle != HandleType() && mEntries[handle.mIndex].generation == handle.mGeneration;
}

template <typename DataType>
DataType* HandlePool<DataType>::Get(HandleType handle) const
{
	return IsValid(handle) ? mEntries[handle.mIndex].instance : nullptr;
}

}
}