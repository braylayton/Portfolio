#ifndef INCLUDED_CORE_BLOCKALLOCATOR_H
#define INCLUDED_CORE_BLOCKALLOCATOR_H

namespace SWGE {
namespace Core {

class BlockAllocator
{
public:
	BlockAllocator(uint32_t blocksize, uint32_t capacity);
	~BlockAllocator();
	
	BlockAllocator(const BlockAllocator&) = delete;
	BlockAllocator& operator=(const BlockAllocator&) = delete;
	
	void* Allocate();
	void Free(void* ptr);


protected:
	//uint32_t GetCapacity() const;
	int8_t* mData;
	uint32_t mBlockSize;
	uint32_t mCapacity;
	uint32_t mSizeOfData;
	int mFreeSlot;
	int mLastSlot;
};

} // Core
} // SWGE

#endif // INCLUDED_CORE_BLOCKALLOCATOR_H

