#ifndef INCLUDED_NETWORKING_UDPSOCKET_H
#define INCLUDED_NETWORKING_UDPSOCKET_H

#include "SocketAddress.h"

namespace SWGE {
namespace Networking {

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();

	bool Open();
	void Close();

	bool Bind(const SocketAddress& fromAddress);
	bool SetBroadcast(bool broadcast);

	int SendTo(const void* buffer, int len, const SocketAddress& toAddress);
	int RecieveFrom(void* buffer, int len, SocketAddress& fromAddress);

private:
	UDPSocket(const UDPSocket&) = delete;
	UDPSocket& operator=(const UDPSocket&) = delete;

	SOCKET mSocket;

};

}
}

#endif // INCLUDED_NETWORKING_UDPSOCKET_H