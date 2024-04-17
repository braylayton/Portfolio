#ifndef INCLUDED_NETWORKING_TCPSOCKET_H
#define INCLUDED_NETWORKING_TCPSOCKET_H

#include "SocketAddress.h"

namespace SWGE {
namespace Networking {

class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

	bool Open();
	void Close();

	bool Connect(const SocketAddress& address);
	bool Bind(const SocketAddress& fromAddress);
	bool Listen(int backLog = 10);
	TCPSocket* Accept(SocketAddress& fromAddress);

	int Send(const void* buffer, int len);
	int Recieve(void* buffer, int len);

private:
	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;

	SOCKET mSocket;

};

} // Networking
} // SWGE



#endif // INCLUDED_NETWORKING_TCPSOCKET_H