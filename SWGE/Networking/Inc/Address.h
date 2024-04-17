#ifndef INCLUDED_NETWORK_ADDRESS_H
#define INCLUDED_NETWORK_ADDRESS_H

#include "Networking.h"

namespace SWGE {
namespace Networking {

class Address
{
public:

	Address();

	Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);

	Address(unsigned int address, unsigned short port);

	unsigned int GetAddress() const { return mAddress; }

	unsigned char GetA() const { return mA; }
	unsigned char GetB() const { return mB; }
	unsigned char GetC() const { return mC; }
	unsigned char GetD() const { return mD; }

	void Set(unsigned int address, unsigned short port);

	sockaddr_in GetSockAddress() const { return mSockAddress; }
	
	unsigned short GetPort() const { return mPort; }
	


private:
	void InitializeAddress();
	sockaddr_in mSockAddress;

	unsigned int mAddress;
	unsigned char mA;
	unsigned char mB;
	unsigned char mC;
	unsigned char mD;

	unsigned short mPort;
};


} // namespace Networking
} // namespace SWGE
#endif //INCLUDED_NETWORK_ADDRESS_H

