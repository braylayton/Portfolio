#ifndef INCLUDED_NETWORKING_OUTPUTMEMORYBITSTREAM_H
#define INCLUDED_NETWORKING_OUTPUTMEMORYBITSTREAM_H

#include "Networking.h"

namespace SWGE {
namespace Networking {

class OutputMemoryBitStream
{
public:

	OutputMemoryBitStream()
		: mBitHead(0)
		, mBuffer(nullptr)
	{
		ReallocBuffer(1500 * 8);
	}

	~OutputMemoryBitStream() { std::free(mBuffer); }

	void WriteBits(uint8_t inData, uint32_t inBitCount);
	void WriteBits(const void* inData, uint32_t inBitCount);

	const char*	GetBufferPtr()		const { return mBuffer; }
	uint32_t GetBitLength()		const { return mBitHead; }
	uint32_t GetByteLength()		const { return (mBitHead + 7) >> 3; }

	void WriteBytes(const void* inData, uint32_t inByteCount) { WriteBits(inData, inByteCount << 3); }


	template< typename T >
	void Write(T inData, uint32_t inBitCount = sizeof(T) * 8)
	{
		ASSERT(std::is_arithmetic< T >::value || std::is_enum< T >::value, "Generic Write only supports primitive data types");
		WriteBits(&inData, inBitCount);
	}

	void Write(bool inData) { WriteBits(&inData, 1); }
	void Write(const Math::Vector3& inVector);
	void Write(const Math::Quaternion& inQuat);

	void Write(const std::string& inString)
	{
		uint32_t elementCount = static_cast< uint32_t >(inString.size());
		Write(elementCount);
		for (const auto& element : inString)
		{
			Write(element);
		}
	}

private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;

};

}
}





#endif