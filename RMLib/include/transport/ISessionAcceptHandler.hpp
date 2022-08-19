#pragma once

class ISessionAcceptHandler
{
public:
    virtual void    OnAccept(SOCKET childSocket) = 0;
};
