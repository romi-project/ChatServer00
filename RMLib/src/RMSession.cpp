#include "romi.hpp"

int		RMSession::GetDesiredEventFlags() const
{
	if (!_outBufferQueue.empty() || !_outBuffer.empty())
		return (EventFlags::Readable | EventFlags::Writable);
	return EventFlags::Readable;
}

void    RMSession::OnRead()
{
	InBuffer::ValueType buf[1460];

	while (true)
	{
		int rbytes = ::recv(GetSocket(), reinterpret_cast<char*>(buf), sizeof(buf), 0);
		if (rbytes == SOCKET_ERROR)
		{
			auto err = WSAGetLastError();
			switch (err)
			{
			case WSAEWOULDBLOCK:
				break;
			default:
				throw WSException(err);
			}
		}
		_inBuffer.insert(_inBuffer.end(), buf, &buf[rbytes]);
	}
}

void    RMSession::OnWrite()
{

}

void    RMSession::Send(const OutBuffer& outBuffer)
{
	_outBufferQueue.push(outBuffer);
}
