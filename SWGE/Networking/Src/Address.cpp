#include "Precompiled.h"
#include "Address.h"

using namespace SWGE;
using namespace Networking;

Address::Address()
{}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
	: mA(a)
	, mB(b)
	, mC(c)
	, mD(d)
	, mPort(port)
{

	InitializeAddress();
	mAddress =  (a << 24) |
				(b << 16) |
				(c << 8)  |
				 d;
}

Address::Address(unsigned int address, unsigned short port)
	: mAddress(address)
	, mPort(port)
{
	InitializeAddress();
}

void  Address::InitializeAddress()
{
	ASSERT(mPort > 0 && mAddress > 0, "[Networking] Port and Address are already Initialized!" );
	memset((char *)&mSockAddress, 0, sizeof(mSockAddress));
	mSockAddress.sin_family = AF_INET;
	mSockAddress.sin_addr.s_addr = INADDR_ANY;
	mSockAddress.sin_port = htons((unsigned short)mPort);
}

void Address::Set(unsigned int address, unsigned short port)
{
	mAddress = address;
	mPort = port;
}