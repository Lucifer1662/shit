#include "strutil.h"
#include "stdfx.h"



std::string wsTos(const std::string& wstr)
{
    return wstr;
}


std::string wsTos(const std::wstring& wstr)
{
    return std::string(wstr.begin(), wstr.end());
}

std::wstring sTows(const std::wstring& str)
{
    return str;
}


std::wstring sTows(const std::string& str)
{
    return std::wstring(str.begin(), str.end());
}


string_t toUtilStr(const std::string& str)
{
#ifdef _UTF16_STRINGS
    return std::wstring(str.begin(), str.end());
#else
    return str;
#endif
}
