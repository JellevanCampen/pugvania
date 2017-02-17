#pragma once
#ifndef ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_
#define ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_

#include "engine.h"

#define DEBUG_UTIL_STRINGIZE_EXPANDED(x) #x // Stringizes an expanded preprocessor macro
#define DEBUG_UTIL_STRINGIZE(x) DEBUG_UTIL_STRINGIZE_EXPANDED(x) // Expands preprocessor macros such as __LINE__ and __FILE__ before stringizing
#define DEBUG_UNIMPLEMENTED g_log("Calling unimplemented function [" __FUNCTION__ "] at " DEBUG_UTIL_STRINGIZE(__FILE__) "(" DEBUG_UTIL_STRINGIZE(__LINE__)")", log::kWarning); // The called functions is not implemented yet
#define DEBUG_BOOTSTRAPPER_FUNCTION g_log("Calling bootstrapper function [" __FUNCTION__ "] at " DEBUG_UTIL_STRINGIZE(__FILE__) "(" DEBUG_UTIL_STRINGIZE(__LINE__)")", log::kError); // The function was called before the bootstrapper could boot its replacement

#define SAFETY_CHECK 1 // Whether or not to perform safety checks

#endif // ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_