#include "std.hpp"
#include "ChatSession.hpp"
#include "ChatServer.hpp"

ChatSession::ChatSession(SOCKET socket, ChatServer* server)
	: RMSession(socket), _server(server)
{
}

ChatSession::~ChatSession()
{
}

void    ChatSession::OnData(const InBuffer& iBuffer)
{
	LOGD << "[R/" << GetRemoteAddr() << "]" << iBuffer.Dump();
}