#include "std.hpp"
#include "util/NetAddress.hpp"

std::string NetAddress::ToString(const SOCKADDR_IN& sockAddr)
{
    char    buf[INET_ADDRSTRLEN];

    ZeroMemory(buf, INET_ADDRSTRLEN);
    auto res = inet_ntop(sockAddr.sin_family, &sockAddr.sin_addr, buf, INET_ADDRSTRLEN);
    if (res == NULL)
        throw ERROR_INVALID_PARAMETER;
    return std::format("{}:{:d}", buf, ntohs(sockAddr.sin_port));
}

std::string NetAddress::ToString(const SOCKADDR_IN6& sockAddr6)
{
    char    buf[INET6_ADDRSTRLEN];

    ZeroMemory(buf, INET6_ADDRSTRLEN);
    auto res = inet_ntop(sockAddr6.sin6_family, &sockAddr6.sin6_addr, buf, INET6_ADDRSTRLEN);
    if (res == NULL)
        throw ERROR_INVALID_PARAMETER;
    return std::format("{}:{:d}", buf, ntohs(sockAddr6.sin6_port));
}

std::string NetAddress::GetSocketAddress(const SOCKET socket)
{
    char        buf[sizeof(SOCKADDR_IN6)];
    int         namelen;

    ZeroMemory(&buf, sizeof(buf));
    namelen = sizeof(buf);
    if (0 != getpeername(socket, reinterpret_cast<sockaddr*>(buf), &namelen))
        return "?.?.?.?";

    const SOCKADDR& sockAddr = *reinterpret_cast<SOCKADDR*>(buf);
    if (sockAddr.sa_family == AF_INET6)
        return ToString(std::bit_cast<SOCKADDR_IN6>(buf));
    return ToString(*reinterpret_cast<SOCKADDR_IN*>(buf));
}
