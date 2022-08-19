#include "std.hpp"
#include "util/Locale.hpp"

std::string Locale::ToString(const std::wstring& wstr)
{
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string str(len, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, str.data(), len, NULL, NULL);
    return str;
}

std::wstring Locale::ToWString(const std::string& str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.length()), NULL, 0);
    std::wstring wstr(len, 0);
    MultiByteToWideChar(CP_ACP, 0, str.data(),static_cast<int>(str.length()), wstr.data(), static_cast<int>(len));
    return wstr;
}
