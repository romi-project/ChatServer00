#include "std.hpp"
#include "util/SocketUtil.hpp"
#include "exception/WSException.hpp"

void SocketUtil::SetOption(SOCKET s, OPTION key, bool val)
{
    SetOption(s, key, val ? "\1" : "\0");
}

void SocketUtil::SetOption(SOCKET s, OPTION key, PCSTR val)
{
    int level, optname;

    switch (key)
    {
    case OPTION::RE_USE_ADDRESS:
		level = SOL_SOCKET;
		optname = SO_REUSEADDR;
        break;
    case OPTION::TCP_NO_DELAY:
		level = IPPROTO_TCP;
		optname = TCP_NODELAY;
        break;
    default:
        throw ERROR_INVALID_PARAMETER;
    }
    auto res = ::setsockopt(s, level, optname, val, static_cast<int>(std::strlen(val)));
    if (res == SOCKET_ERROR)
        throw WSException(WSAGetLastError());
}

void SocketUtil::SetNonBlocking(SOCKET s, bool enable)
{
    u_long arg = enable ? TRUE : FALSE;
    auto res = ::ioctlsocket(s, FIONBIO, &arg);
    if (res == SOCKET_ERROR)
        throw WSException(WSAGetLastError());
}
