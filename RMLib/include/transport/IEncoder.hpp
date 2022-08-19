#pragma once

class IEncoder
{
	virtual void    Encode(const OutBuffer& outBuffer, std::vector<OutBuffer::ValueType>& output) = 0;
};