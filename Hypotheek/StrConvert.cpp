
//#include "pch.h"

#include "StrConvert.h"

#include "pch.h"


#include <stringapiset.h>

#include <Utilities/StrUtils.h>

namespace StrConvert
{


std::wstring Utf8ToUtf16(const std::string& string)
{
//    std::string ansi = "héllo";
    int size = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, nullptr, 0);
    std::wstring wide(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, &wide[0], size);
    return wide;
}

std::string Utf16ToUtf8(const std::wstring& string)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, string.c_str(), string.size(), nullptr, 0, 0, FALSE);
    std::string utf8(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, string.c_str(), string.size(), &utf8[0], size, 0, FALSE);
    return utf8;
}

bool IsDouble(const std::wstring& text)
{
    return Str::IsDouble(Utf16ToUtf8(text));
}

double ToDouble(const std::wstring& text)
{
    return Str::ToDouble(Utf16ToUtf8(text));
}

} // namespace StrConvert