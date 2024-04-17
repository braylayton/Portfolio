#include "Precompiled.h"
#include "BlockAllocator.h"

#include "Debug.h"

using namespace SWGE;
using namespace Core;

BlockAllocator::BlockAllocator(uint32_t blocksize, uint32_t capacity)
	: mBlockSize(blocksize)
	, mCapacity(capacity)
	, mFreeSlot(0)
	, mLastSlot(-2) // initialize mLastSlot to a number not available in the blockAllocator
	, mSizeOfData(blocksize * capacity)

{
	ASSERT(blocksize != 0, "[BlockAllocator] BlockSize Cannont be zero");
	ASSERT(capacity != 0, "[BlockAllocator] Capacity Cannont be zero");
	mData = reinterpret_cast<int8_t*>(malloc(blocksize * capacity));
	for (uint32_t i = 0; i < capacity; i++)
	{
		if (i+1 != capacity)
		{
			mData[i * blocksize] = i + 1;
		}
		else
		{
			mData[i * blocksize] = -1;
		}
	}
}
BlockAllocator::~BlockAllocator()
{
	free(mData);
}

void* BlockAllocator::Allocate()
{
	if (mFreeSlot != -1)
	{
		int8_t* retptr = &mData[mFreeSlot * mBlockSize];
		mFreeSlot = mData[mFreeSlot * mBlockSize];
		return retptr;
	}
	return nullptr;
}
void BlockAllocator::Free(void* ptr)
{
	int8_t* ptrInt = reinterpret_cast<int8_t*>(ptr);
	// ONLY FREE ONCE! This check will work for free(data), free(data) but not for free(data), free(data2), free(data)
	if (*ptrInt != mLastSlot) 
	{
		std::ptrdiff_t distance = ptrInt - mData;	
		ASSERT(distance >= 0 && distance <= (mBlockSize * mCapacity), "[BlockAllocator]{Free()} distance is less than 0 or Greater than The block size");
		*ptrInt = mFreeSlot;
		mLastSlot = mFreeSlot;
		mFreeSlot = static_cast<int>(distance) / mBlockSize;
	}

}