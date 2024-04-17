#ifndef INCLUDED_NETWORKING_SOCKETUTIL_H
#define INCLUDED_NETWORKING_SOCKETUTIL_H

namespace SWGE {
namespace Networking{

enum SocketAddressFamily
{
	INET = AF_INET,
	//INET6 = AF_INET6
};

class SocketUtil
{
public:
	static void			ReportError( const char* inOperationDesc );
	static int			GetLastError();

private:

};

} // Networking
} // SWGE

#endif