#include "Precompiled.h"
#include "TCPSocket.h"

using namespace SWGE;
using namespace Networking;

TCPSocket::TCPSocket()
	: mSocket(INVALID_SOCKET)
{
}
TCPSocket::~TCPSocket()
{
	Close();
}

bool TCPSocket::Open()
{
	ASSERT(mSocket == INVALID_SOCKET, "[TCPSocket]{Open()} Socket already opened!");
	 mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
	{
		LOG("[TCPSocket] Failed to open socket.");
		return false;
	}
}
void TCPSocket::Close()
{
	if (mSocket != INVALID_SOCKET)
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}
}

bool TCPSocket::Connect(const SocketAddress& address)
{
	return -1;
}
bool TCPSocket::Bind(const SocketAddress& fromAddress)
{
	return -1;
}
bool TCPSocket::Listen(int backLog)
{
	return -1;
}
TCPSocket* TCPSocket::Accept(SocketAddress& fromAddress)
{
	TCPSocket* sock;
	return sock;
}

int TCPSocket::Send(const void* buffer, int len)
{
	return -1;
}
int TCPSocket::Recieve(void* buffer, int len)
{
	return -1;
}