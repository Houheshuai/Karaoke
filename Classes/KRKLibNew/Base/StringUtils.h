#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <stdarg.h>
#include <string>
#include <sstream>

#include "Platform/PlatformMacros.h"

namespace StringUtils 
{

template<typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

std::string format(const char* format, ...) FORMAT_PRINTF(1, 2);
    
} // namespace StringUtils {


#endif //__STRING_UTILS_H__
