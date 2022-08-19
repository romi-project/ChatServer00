#pragma once

class ChatServer;

class ChatSession : public RMSession
{
private:
    ChatServer* _server;

public:
    ChatSession(SOCKET socket, ChatServer* server);
    virtual ~ChatSession();

    ChatSession(const ChatSession&) = delete;
    ChatSession(ChatSession&&) = delete;
    ChatSession& operator= (const ChatSession&) = delete;
    ChatSession& operator= (ChatSession&&) = delete;

    virtual void    OnData(const InBuffer& iBuffer) override;

    virtual void    OnConnect() override
    {
        LOGI << " 에서 채팅 클라이언트가 연결되었습니다.";
    }

    virtual void    OnDisconnect() override
    {
        LOGI << " 에서 채팅 클라이언트 연결이 종료되었습니다.";
    }
};
