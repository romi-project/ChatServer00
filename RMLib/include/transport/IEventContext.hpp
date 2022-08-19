#pragma once
#include "transport/EventFlags.hpp"

class IEventContext
{
public:
    virtual ~IEventContext() {}

    virtual int         GetDesiredEventFlags() const = 0;
    virtual SOCKET      GetSocket() const = 0;
    virtual void        OnRead() = 0;
    virtual void        OnWrite() = 0;
};
