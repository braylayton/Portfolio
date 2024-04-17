#ifndef INCLUDED_NETWORKING_SOCKETADDRESS_H
#define INCLUDED_NETWORKING_SOCKETADDRESS_H

namespace SWGE {
namespace Networking {

class SocketAddress
{
public:
	SocketAddress();
	SocketAddress(const char*  host, uint16_t port);
	SocketAddress(uint16_t port);

	const char* GetHost() const;

private:
friend class TCPSocket;
friend class UDPSocket;

sockaddr_in* GetAsSockAddrIn()				{ return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
const sockaddr_in* GetAsSockAddrIn() const	{ return reinterpret_cast<const sockaddr_in*>(&mSockAddr); }

uint32_t& GetIPV4()							{ return *reinterpret_cast<uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
const uint32_t& GetIPV4() const				{ return *reinterpret_cast<const uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }

uint16_t&  GetPort()						{ return *reinterpret_cast<uint16_t*>(&GetAsSockAddrIn()->sin_port); }
const uint16_t&  GetPort() const			{ return *reinterpret_cast<const uint16_t*>(&GetAsSockAddrIn()->sin_port); }

size_t GetSize() const						{ return sizeof(sockaddr); }
sockaddr mSockAddr;

};



}
}



#endif // INCLUDED_NETWORKING_SOCKETADDRESS_H