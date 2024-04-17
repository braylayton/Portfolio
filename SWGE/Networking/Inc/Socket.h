#ifndef INCLUDED_NETWORK_SOCKET_H
#define INCLUDED_NETWORK_SOCKET_H

#include "Networking.h"

namespace SWGE {
namespace Networking{


class Socket
{
public:

	Socket();
	~Socket();


	bool Open(unsigned short port);
	void Close();

	bool IsOpen() const;

	//bool Send(const Address & destination, const void * data, int size);
//	int Receive(Address & sender, void * data, int size);

private:

	bool InitializeSockets();

	int mHandle;
//	Address mAddress;
};


}
}
#endif // !INCLUDED_NETWORK_SOCKET_H