#include "Precompiled.h"
#include "Socket.h"

using namespace SWGE;
using namespace Networking;


Socket::Socket()
{
	InitializeSockets();
}
Socket::~Socket()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}

bool Socket::InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSADATA WsaData;
	return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
	return true;
#endif
}

bool Socket::Open(unsigned short port)
{
	mHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (mHandle <= 0)
	{
		LOG("failed to create socket\n");
		return false;
	}

	//if (bind(mHandle, (const sockaddr*)&mAddress.GetSockAddress(), sizeof(sockaddr_in)) < 0)
	//{
	//	LOG("failed to bind socket\n");
	//	Close();
	//	return false;
	//}

	// make socket non-blocking
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

	int nonBlocking = 1;
	if (fcntl(m_handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		std::cout << ("failed to set non-blocking\n");
		return false;
	}
#elif PLATFORM == PLATFORM_WINDOWS

	DWORD nonBlocking = 1;
	if (ioctlsocket(mHandle, FIONBIO, &nonBlocking) != 0)
	{
		 LOG("failed to set non-blocking\n");
		return false;
	}
#endif
	return true;
}

void Socket::Close()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		close(mHandle);
#elif PLATFORM == PLATFORM_WINDOWS
	closesocket(mHandle);
#endif
}

bool Socket::IsOpen() const
{
	return mHandle > 0;
}

//bool Socket::Send(const Address& destination, const void * data, int size)
//{
//	int sent_bytes = sendto(destination.GetPort(), (const char*)data, size, 0, (sockaddr*)destination.GetSockAddress(), sizeof(sockaddr));
//
//	if (sent_bytes != size)
//	{
//		LOG("failed to send packet\n");
//		return false;
//	}
//}
//int Socket::Receive( Address& sender, void * data, int size)
//{
//	sockaddr_in from;
//	int fromLength = sizeof(from);
//
//	int bytes = recvfrom(mHandle, (char*)data,size, 0, (sockaddr*)&from, &fromLength);
//
//	if (bytes <= 0)
//		bytes;
//
//	unsigned int from_address = ntohl(from.sin_addr.s_addr);
//
//	unsigned int from_port = ntohs(from.sin_port);
//	sender.Set(from_address, from_port);
//
//	return bytes;
//}
//
