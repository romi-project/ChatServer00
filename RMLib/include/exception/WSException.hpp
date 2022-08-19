#pragma once

class WSException
{
private:
    int _wsError;

public:
    WSException(int error)
        : _wsError(error)
    {
    }

    int GetError() const { return _wsError; }
};
