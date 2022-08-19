std::string Dump() const
{
    std::ostringstream result;
    for (const auto& x : _buffer)
    {
        if (result.tellp() > 0)
            result << " ";
        result << std::format("{:02X}", static_cast<int>(x));
    }
    return result.str();
}
