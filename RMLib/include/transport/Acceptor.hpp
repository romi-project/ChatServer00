#pragma once

template<Session T>
class Acceptor final : public IEventContext
{
private:
    SOCKET                  _socket;
    NET_ADDRESS_INFO        _addrInfo;
    int                     _tcpBacklog;
    std::mutex              _mutex;
    ISessionAcceptHandler*  _acceptHandler;

public:
    Acceptor(const std::string& netAddress, ISessionAcceptHandler* acceptHandler, int tcpBacklog = 20)
        : _socket(INVALID_SOCKET)
        , _acceptHandler(acceptHandler)
        , _tcpBacklog(tcpBacklog)
    {
        const auto wstrHost = Locale::ToWString(netAddress);
        USHORT portNumber;

        std::memset(&_addrInfo, 0, sizeof(_addrInfo));
        auto res = ParseNetworkString(wstrHost.c_str(), NET_STRING_IP_ADDRESS, &_addrInfo, &portNumber, NULL);
        if (res != ERROR_SUCCESS)
            throw res;

        LOGV << "네트워크 주소 '" << netAddress << "' 를 다음과 같이 파싱했습니다.";
        LOGV << "IPv4 - " << NetAddress::ToString(_addrInfo.Ipv4Address);
    }

    virtual ~Acceptor() { closesocket(_socket); }

    SOCKET      GetSocket() const override
    {
        return _socket;
    }

    int     GetDesiredEventFlags() const override
    {
        return EventFlags::Readable;
    }

    void    OnRead() override
    {
        SOCKADDR_IN addr;
        auto addrLen = static_cast<socklen_t>(sizeof(addr));

        ZeroMemory(&addr, sizeof(addr));
        SOCKET childSocket = ::accept(_socket, reinterpret_cast<LPSOCKADDR>(&addr), &addrLen);
        if (childSocket == INVALID_SOCKET)
        {
            const auto nerror = WSAGetLastError();
            switch (nerror)
            {
                case WSAECONNRESET:
                case WSAEWOULDBLOCK:
                    LOGD << "소켓을 accept하는 중, 에러코드 [" << nerror << "]가 발생했습니다. 무시 후 계속합니다.";
                    break;
                default:
                    throw WSException(nerror);
            }
        }
        LOGV << "새롭게 accept된 소켓을 처리기로 전달합니다.";
        _acceptHandler->OnAccept(childSocket);
        LOGV << "새롭게 accept된 소켓을 처리기로 전달하여 처리가 완료되었습니다.";
    }

    void    OnWrite() override { throw ERROR_INVALID_ACCESS; }

    void    Listen()
    {
        synchronized(_mutex)
        {
            if (_socket != INVALID_SOCKET)
                throw new WSException(WSAEALREADY);
            const auto& sockAddr = _addrInfo.Ipv4Address;
            _socket = ::socket(sockAddr.sin_family, SOCK_STREAM, IPPROTO_TCP);
            LOGV << "Acceptor에서 Listen을 위한 소켓이 생성되었습니다. (" << NetAddress::ToString(sockAddr) << ")";

            if (SOCKET_ERROR == ::bind(_socket,  reinterpret_cast<LPSOCKADDR>(&sockAddr), sizeof(sockAddr)))
                throw WSException(WSAGetLastError());
            if (SOCKET_ERROR == ::listen(_socket, _tcpBacklog))
                throw WSException(WSAGetLastError());
            LOGI << NetAddress::ToString(sockAddr) << "에서 연결을 대기중입니다.";
        }
    }
};
