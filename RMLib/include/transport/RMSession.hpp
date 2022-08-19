#pragma once

class RMSession : public IEventContext
{
private:
    SOCKET                              _socket;
    const std::string                   _remoteAddr;
    std::vector<InBuffer::ValueType>    _inBuffer;
    std::vector<OutBuffer::ValueType>   _outBuffer;
    std::queue<OutBuffer>               _outBufferQueue;
    std::mutex                          _mutex;

public:
    RMSession(SOCKET socket)
        : _socket(socket)
        , _remoteAddr(NetAddress::GetSocketAddress(socket))
        , _inBuffer(1024)
        , _outBuffer(1024)
        , _outBufferQueue()
    {
    }

    virtual ~RMSession() { closesocket(_socket); }

    RMSession(const RMSession&) = delete;
    RMSession(RMSession&&) = delete;
    RMSession& operator= (const RMSession&) = delete;
    RMSession& operator= (RMSession&&) = delete;

    virtual void        OnData(const InBuffer& iBuffer) = 0;


    virtual SOCKET      GetSocket() const override final
    { 
        return _socket; 
    }

    virtual int         GetDesiredEventFlags() const override final;
    virtual void        OnRead() override final;
    virtual void        OnWrite() override final;

    virtual void        OnConnect()     { }
    virtual void        OnDisconnect()  { }
    
    void                Send(const OutBuffer& outBuffer);

    const std::string& GetRemoteAddr() const { return _remoteAddr;  }
};

template<typename T>
concept Session = std::convertible_to<T*, RMSession*>;
