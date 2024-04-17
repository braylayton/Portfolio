#include "Precompiled.h"
#include "UDPSocket.h"

using namespace SWGE;
using namespace Networking;

UDPSocket::UDPSocket()
	: mSocket(INVALID_SOCKET)
{
}

UDPSocket::~UDPSocket()
{
	Close();
}

bool UDPSocket::Open()
{
	ASSERT(mSocket == INVALID_SOCKET, "[UDPSocket]{Open()} Socket already opened!");
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		LOG("[UDPSocket] Failed to open socket.");
		return false;
	}
	return true;
}

void UDPSocket::Close()
{
	if (mSocket != INVALID_SOCKET)
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}
}

bool UDPSocket::Bind(const SocketAddress& address)
{
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return false;
	}

	int result = bind(mSocket, &address.mSockAddr, address.GetSize());
	if (result == SOCKET_ERROR)
	{
		LOG("[UDPSocket] Failed to bind socket. Error: %d", WSAGetLastError());
		return false;
	}
	return true;
}

bool UDPSocket::SetBroadcast(bool broadcast)
{
	// homework
	// SetSockOpt a way for you to toggle what mode your socket will be
	return false;
}

int  UDPSocket::SendTo(const void* buffer, int len, const SocketAddress& toAddress)
{
	ASSERT(len > 0, "[UDPSocket] Invalid buffer length");
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return SOCKET_ERROR;
	}

	int byteSent = sendto(mSocket,
		static_cast<const char*>(buffer),
		len, 0, &toAddress.mSockAddr, toAddress.GetSize());
	if (byteSent < 0)
	{
		LOG("[UDPSocket] Failed to send data. Error: %d", WSAGetLastError);
		return SOCKET_ERROR;
	}
	return byteSent;

}
int UDPSocket::RecieveFrom(void* buffer, int len, SocketAddress& fromAddress)
{
	int fromLength = fromAddress.GetSize();
	int bytesRead = recvfrom(mSocket, static_cast<char*>(buffer), len, 0, &fromAddress.mSockAddr, &fromLength);

	if (bytesRead >= 0)
	{
		return bytesRead;
	}
	else
	{
		int error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK)
		{
			return 0;
		}
		else if (error == WSAECONNRESET)
		{
			// This can happen if a client closed and we havent dc'd yet.
			//this is the ICMP message being sent back saying the port on that comuter is closed
			LOG("[UDPSocket] Connection reset");
			return -WSAECONNRESET;
		}
		else
		{
			LOG("[UDPSocket] Error on recieve");
			return -error;
		}
	}

}