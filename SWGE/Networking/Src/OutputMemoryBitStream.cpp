#include "Precompiled.h"
#include "OutputMemoryBitStream.h"

using namespace SWGE;
using namespace Networking;

inline uint32_t ConvertToFixed(float inNumber, float inMin, float inPrecision)
{
	return static_cast< int > ((inNumber - inMin) / inPrecision);
}

void OutputMemoryBitStream::WriteBits(uint8_t inData,
	uint32_t inBitCount)
{
	uint32_t nextBitHead = mBitHead + static_cast< uint32_t >(inBitCount);

	if (nextBitHead > mBitCapacity)
	{
		ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));
	}

	//calculate the byteOffset into our buffer
	//by dividing the head by 8
	//and the bitOffset by taking the last 3 bits
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	uint8_t currentMask = ~(0xff << bitOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

	//calculate how many bits were not yet used in
	//our target byte in the buffer
	uint32_t bitsFreeThisByte = 8 - bitOffset;

	//if we needed more than that, carry to the next byte
	if (bitsFreeThisByte < inBitCount)
	{
		//we need another byte
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}

	mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void* inData, uint32_t inBitCount)
{
	const char* srcByte = static_cast< const char* >(inData);
	//write all the bytes
	while (inBitCount > 8)
	{
		WriteBits(*srcByte, 8);
		++srcByte;
		inBitCount -= 8;
	}
	//write anything left
	if (inBitCount > 0)
	{
		WriteBits(*srcByte, inBitCount);
	}
}

void OutputMemoryBitStream::Write(const Math::Vector3& inVector)
{
	Write(inVector.x);
	Write(inVector.y);
	Write(inVector.z);
}


void OutputMemoryBitStream::Write(const Math::Quaternion& inQuat)
{
	float precision = (2.f / 65535.f);
	Write(ConvertToFixed(inQuat.x, -1.f, precision), 16);
	Write(ConvertToFixed(inQuat.y, -1.f, precision), 16);
	Write(ConvertToFixed(inQuat.z, -1.f, precision), 16);
	Write(inQuat.w < 0);
}



void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitLength)
{
	if (mBuffer == nullptr)
	{
		//just need to memset on first allocation
		mBuffer = static_cast<char*>(std::malloc(inNewBitLength >> 3));
		memset(mBuffer, 0, inNewBitLength >> 3);
	}
	else
	{
		//need to memset, then copy the buffer
		char* tempBuffer = static_cast<char*>(std::malloc(inNewBitLength >> 3));
		memset(tempBuffer, 0, inNewBitLength >> 3);
		memcpy(tempBuffer, mBuffer, mBitCapacity >> 3);
		std::free(mBuffer);
		mBuffer = tempBuffer;
	}

	//handle realloc failure
	//...
	mBitCapacity = inNewBitLength;
}