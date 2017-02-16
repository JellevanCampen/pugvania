#pragma once
#ifndef ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_
#define ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_

#include "engine.h"

#define STRINGIZE_EXPANDED(x) #x // Stringizes an expanded preprocessor macro
#define STRINGIZE(x) STRINGIZE_EXPANDED(x) // Expands preprocessor macros such as __LINE__ and __FILE__ before stringizing
#define DEBUG_UNIMPLEMENTED g_log("Using unimplemented function [" __FUNCTION__ "] at " STRINGIZE(__FILE__) "(" STRINGIZE(__LINE__)")", log::kWarning);

#define SAFETY_CHECK 1 // Whether or not to perform safety checks

#endif // ENGINE_COMMON_UTILITY_DEBUG_DEFINES_H_