#pragma once
#include <string>
#include "stdfx.h"

std::string wsTos(const std::string& wstr);
std::string wsTos(const std::wstring& wstr);
std::wstring sTows(const std::wstring& str);
std::wstring sTows(const std::string& str);
string_t toUtilStr(const std::string& str);