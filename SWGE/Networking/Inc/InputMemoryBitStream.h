#ifndef INCLUDED_INPUTMEMORYBITSTREAM_H
#define INCLUDED_INPUTMEMORYBITSTREAM_H

#include "Networking.h"

namespace SWGE {
namespace Networking{

class InputMemoryBitStream
{
public:

	InputMemoryBitStream(char* inBuffer, uint32_t inBitCount) 
		: mBuffer(inBuffer)
		, mBitCapacity(inBitCount)
		, mBitHead(0)
		, mIsBufferOwner(false) {}

	InputMemoryBitStream(const InputMemoryBitStream& inOther) 
		: mBitCapacity(inOther.mBitCapacity)
		, mBitHead(inOther.mBitHead)
		, mIsBufferOwner(true)
	{
		//allocate buffer of right size
		int byteCount = mBitCapacity / 8;
		mBuffer = static_cast< char* >(malloc(byteCount));
		//copy
		memcpy(mBuffer, inOther.mBuffer, byteCount);
	}

	~InputMemoryBitStream() { if (mIsBufferOwner) { free(mBuffer); }; }

	const char*	GetBufferPtr()		const { return mBuffer; }
	uint32_t GetRemainingBitCount() 	const { return mBitCapacity - mBitHead; }

	void ReadBits(uint8_t& outData, uint32_t inBitCount);
	void ReadBits(void* outData, uint32_t inBitCount);

	void ReadBytes(void* outData, uint32_t inByteCount) { ReadBits(outData, inByteCount << 3); }

	template< typename T >
	void Read(T& inData, uint32_t inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Read only supports primitive data types");
		ReadBits(&inData, inBitCount);
	}

	void Read(uint32_t& outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }
	void Read(int& outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }
	void Read(float& outData) { ReadBits(&outData, 32); }

	void Read(uint16_t& outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }
	void Read(int16_t& outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }

	void Read(uint8_t& outData, uint32_t inBitCount = 8) { ReadBits(&outData, inBitCount); }
	void Read(bool& outData) { ReadBits(&outData, 1); }

	void Read(Math::Quaternion& outQuat);

	void ResetToCapacity(uint32_t inByteCapacity) { mBitCapacity = inByteCapacity << 3; mBitHead = 0; }


	void Read(std::string& inString)
	{
		uint32_t elementCount;
		Read(elementCount);
		inString.resize(elementCount);
		for (auto& element : inString)
		{
			Read(element);
		}
	}

	void Read(Math::Vector3& inVector);

private:
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
	bool mIsBufferOwner;

};

} // Networking
} // SWGE



#endif // INCLUDED_INPUTMEMORYBITSTREAM_H