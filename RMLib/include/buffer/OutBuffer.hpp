#pragma once

// Outbound 버퍼를 래핑
class OutBuffer
{
public:
    typedef std::byte   ValueType;

private:
    std::vector<ValueType>    _buffer;

public:
    OutBuffer()
    {
        _buffer.reserve(32);
    }

    OutBuffer(size_t initialCapacity)
    {
        _buffer.reserve(initialCapacity);
    }

    template<typename T>
    void    Put(const T& data)
    {
        std::array<ValueType, sizeof(T)> value_arrays = std::bit_cast<decltype(value_arrays)>(data);
        _buffer.insert(_buffer.end(), value_arrays.begin(), value_arrays.end());
    }

    template<std::output_iterator<ValueType> OutputIterator>
    void    CopyTo(OutputIterator outputIter)
    {
        std::copy(_buffer.begin(), _buffer.end(), outputIter);
    }

    #include "HexDump.ipp"
};
