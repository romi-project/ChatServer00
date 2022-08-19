#pragma once

#include "ChatSession.hpp"

class ChatServer : public RMServer<ChatSession>
{
public:
    ChatServer(const std::string& listenAddr, int tcpBacklog = 20)
        : RMServer<ChatSession>(listenAddr, tcpBacklog)
    {
    }

    virtual void    OnAccept(SOCKET childSocket) override
    {
        Construct(childSocket, this);
    }

    virtual void    OnBegin() override
    {
        LOGI << "ChatServer 시작합니다~";
    }

    virtual void    OnEnd() override
    {
        LOGI << "ChatServer 종료합니다~";

    }
};
