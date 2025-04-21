#pragma once

#include <string>


namespace StrConvert
{
std::wstring Utf8ToUtf16(const std::string& string);
std::string Utf16ToUtf8(const std::wstring& string);
bool IsDouble(const std::wstring& text);
double ToDouble(const std::wstring& text);
};

