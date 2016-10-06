#pragma once
#ifndef ENGINE_UTILITY_PATTERNS_WINDOWSTERMINALCOLORS_H_
#define ENGINE_UTILITY_PATTERNS_WINDOWSTERMINALCOLORS_H_

namespace engine {

  // Represents a channel that accepts log messages and sends them to an 
  // output channel. 
  enum WindowsTerminalColors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2, 
    AQUA = 3, 
    RED = 4,
    PURPLE = 5, 
    YELLOW = 6, 
    WHITE = 7, 
    GRAY = 8, 
    LIGHT_BLUE = 9, 
    LIGHT_GREEN = 10,
    LIGHT_AQUA = 11,
    LIGHT_RED = 12,
    LIGHT_PURPLE = 13,
    LIGHT_YELLOW = 14,
    LIGHT_WHITE = 15,
  };

} // namespace

#endif // ENGINE_UTILITY_PATTERNS_WINDOWSTERMINALCOLORS_H_