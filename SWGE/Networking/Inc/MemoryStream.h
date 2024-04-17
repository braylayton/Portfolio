#pragma once

#include "SocketAddress.h"
#include "StreamWriter.h"
#include "StreamReader.h"

namespace SWGE {
namespace Networking {

class MemoryStream
{
public:
	MemoryStream() = default;
	MemoryStream(uint32_t capacity);
	MemoryStream(const uint8_t* data, uint32_t size, bool takeOwnerShip = false);
	~MemoryStream();


	const uint8_t* GetData() const	{ return mBuffer; }
	uint32_t GetHead() const		{ return mHead; }
	uint32_t GetHead() const		{ return mCapacity; }

	void Reset()					{ mHead = 0; }

private:
	MemoryStream(const MemoryStream&) = delete;
	MemoryStream& operator=(const MemoryStream&) = delete;

	friend class StreamReader;
	friend class StreamWriter;

	void ReallocBuffer(uint32_t newCapacity);

	uint8_t* mBuffer{ nullptr };
	uint32_t mHead{ 0 };
	uint32_t mCapacity{ 0 };

};



} // Networking
} // SWGE