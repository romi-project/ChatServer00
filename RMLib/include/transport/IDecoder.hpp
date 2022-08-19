#pragma once

class IDecoder
{
	virtual void    Decode(const InBuffer::ValueType* buf, InBuffer::SizeType length, std::queue<InBuffer>& output) = 0;
};