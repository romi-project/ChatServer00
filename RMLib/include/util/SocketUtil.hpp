#pragma once

class SocketUtil
{
public:
    SocketUtil() = delete;
    SocketUtil(const SocketUtil&) = delete;
    SocketUtil(SocketUtil&&) = delete;
    SocketUtil& operator= (const SocketUtil&) = delete;
    ~SocketUtil() = delete;

	enum class OPTION
	{
		RE_USE_ADDRESS,
		TCP_NO_DELAY
	};

    static void SetOption(SOCKET s, OPTION key, bool val);
    static void SetOption(SOCKET s, OPTION key, PCSTR val);
    static void SetNonBlocking(SOCKET s, bool enable);
};
