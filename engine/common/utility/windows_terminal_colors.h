#pragma once
#ifndef ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_
#define ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_

#include "common\datatypes\color_types.h"

namespace engine {

// Human-readable names for all the Windows terminal colors.
enum class WindowsTerminalColors {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2, 
  CYAN = 3, 
  RED = 4,
  MAGENTA = 5, 
  YELLOW = 6, 
  GRAY = 7, 
  DARKGRAY = 8, 
  LIGHT_BLUE = 9, 
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_YELLOW = 14,
  WHITE = 15,
};

static cRGBi GetColor(WindowsTerminalColors color_name) {
  switch (color_name) {
   case WindowsTerminalColors::BLACK: return cRGBi(0, 0, 0);
   case WindowsTerminalColors::BLUE: return cRGBi(0, 0, 128);
   case WindowsTerminalColors::GREEN: return cRGBi(0, 128, 0);
   case WindowsTerminalColors::CYAN: return cRGBi(0, 128, 128);
   case WindowsTerminalColors::RED: return cRGBi(128, 0, 0);
   case WindowsTerminalColors::MAGENTA: return cRGBi(128, 0, 128);
   case WindowsTerminalColors::YELLOW: return cRGBi(128, 128, 0);
   case WindowsTerminalColors::GRAY: return cRGBi(192, 192, 192);
   case WindowsTerminalColors::DARKGRAY: return cRGBi(128, 128, 128);
   case WindowsTerminalColors::LIGHT_BLUE: return cRGBi(0, 0, 255);
   case WindowsTerminalColors::LIGHT_GREEN: return cRGBi(0, 255, 0);
   case WindowsTerminalColors::LIGHT_CYAN: return cRGBi(0, 255, 255);
   case WindowsTerminalColors::LIGHT_RED: return cRGBi(255, 0, 0);
   case WindowsTerminalColors::LIGHT_MAGENTA: return cRGBi(255, 0, 255);
   case WindowsTerminalColors::LIGHT_YELLOW: return cRGBi(255, 255, 0);
   case WindowsTerminalColors::WHITE: return cRGBi(255, 255, 255);
  }
}

static WindowsTerminalColors GetClosestWindowsTerminalColor(cRGBi color) {
  // TODO(Jelle): implement
}

} // namespace

#endif // ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_