#pragma once

// Inbound 버퍼를 래핑
class InBuffer
{
public:
    typedef std::byte               ValueType;
    typedef std::vector<ValueType>  BufferType;
    typedef BufferType::size_type   SizeType;

private:
    std::vector<ValueType>            _buffer;
    std::vector<ValueType>::size_type _pos;

public:
    template<std::input_iterator InputIterator>
    InBuffer(InputIterator begin, InputIterator end)
        : _buffer(), _pos()
    {
        _buffer.assign(begin, end);
    }

    InBuffer(void* buf, size_t size)
        : _buffer(), _pos()
    {
        _buffer.reserve(size);
        std::memcpy(_buffer.data(), buf, size);
    }

    template<typename T>
    const T&   Get()
    {
        if (_buffer.size() - _pos < sizeof(T))
            throw ERROR_HANDLE_EOF;
        const T& ret = *reinterpret_cast<T*>(&_buffer[_pos]);
        _pos += sizeof(T);
        return ret;
    }

    #include "HexDump.ipp"
};
