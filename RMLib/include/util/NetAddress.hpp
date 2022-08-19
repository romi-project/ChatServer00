#pragma once

class NetAddress
{
public:
    NetAddress() = delete;
    NetAddress(const NetAddress&) = delete;
    NetAddress(NetAddress&&) = delete;
    NetAddress& operator= (const NetAddress&) = delete;
    ~NetAddress() = delete;

    static std::string ToString(const SOCKADDR_IN& sockAddr);
    static std::string ToString(const SOCKADDR_IN6& sockAddr6);
    static std::string GetSocketAddress(const SOCKET socket);
};
