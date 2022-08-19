#pragma once

class   Locale
{
public:
    Locale() = delete;
    Locale(const Locale&) = delete;
    Locale(Locale&&) = delete;
    Locale& operator= (const Locale&) = delete;
    ~Locale() = delete;

    static std::string ToString(const std::wstring& wstr);
    static std::wstring ToWString(const std::string& str);
};
