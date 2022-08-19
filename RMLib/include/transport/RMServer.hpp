#pragma once

template<Session T>
class RMServer : public ISessionAcceptHandler
{
private:
    struct SessionNode
    {
        SessionNode() = delete;
        ~SessionNode() = delete;
        SessionNode(const SessionNode&) = delete;
        SessionNode(SessionNode&&) = delete;
        SessionNode& operator=(const SessionNode&) = delete;
        SessionNode& operator=(SessionNode&&) = delete;

        bool    Active;
        T       Session;
    };

public:
    typedef T                           SessionType;
    typedef Acceptor<T>                 AcceptorType;
    typedef std::allocator<SessionNode> AllocatorType;

private:
    const std::string   _listenAddr;

    bool                _stopTriggered;
    AcceptorType        _acceptor;
    AllocatorType       _allocator;

    SessionNode*        _sockets;
    size_t              _socketCount;
    std::mutex          _mutex;

    void Run()
    {
        OnBegin();
        while (!_stopTriggered)
        {
            int nfds = 0;
            fd_set rfds{};
            fd_set wfds{};

            FD_ZERO(rfds);
            FD_ZERO(wfds);
            for (size_t i = 0; i < _socketCount; ++i)
            {
                const auto& soc = _sockets[i];
                if (!soc.Active) continue;
                const flag = soc.GetDesiredEventFlag();
            }
        }
        OnEnd();
    }

protected:
    template<typename... Types>
    void    Construct(SOCKET socket, Types&&... arguments)
    {
        SessionNode* nodePtr = nullptr;

        synchronized(_mutex)
        {
            for (size_t i = 0; i < MAX_SOCKETS; ++i)
            {
                if (!_sockets[i].Active)
                {
                    nodePtr = &_sockets[i];
                    nodePtr->Active = true;
                    break;
                }
            }
        }
        if (nodePtr == nullptr)
        {
            LOGW << "새로운 소켓을 accept 하였으나, 최대 동시 소켓 제한 " << MAX_SOCKETS << "개에 이미 도달하여 연결을 거부합니다.";
            closesocket(socket);
            return;
        }
        std::construct_at(&nodePtr->Session, socket, arguments...);
    }


public:
    RMServer(const std::string& listenAddr, int tcpBacklog = 20)
        : _listenAddr(listenAddr)
        , _stopTriggered()
        , _acceptor(listenAddr, this, tcpBacklog)
        , _allocator()
        , _sockets(_allocator.allocate(MAX_SOCKETS))
        , _socketCount()
    {
        ZeroMemory(_sockets, sizeof(SessionNode) * MAX_SOCKETS);
    }

    ~RMServer()
    {
        _allocator.deallocate(_sockets, MAX_SOCKETS);
    }

    void    Start()
    {
        _acceptor.Listen();
        Run();
    }

    void    Stop()
    {
        _stopTriggered = true;
    }

    virtual void    OnAccept(SOCKET childSocket) = 0;
    virtual void    OnBegin() { }
    virtual void    OnEnd() { }
};
