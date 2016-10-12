#pragma once
#ifndef ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_
#define ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_

#include <limits>
#include "common\datatypes\color_types.h"
#include "common\patterns\enum_class_iterator.h"

namespace engine {

// Human-readable names for all the Windows terminal colors.
enum class WindowsTerminalColor {
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
  First = BLACK, 
  Last = WHITE
};

// Utility class to convert from and to Windows terminal colors.
namespace WindowsTerminalColorUtility {

  static cRGBi GetColor(WindowsTerminalColor color_name) {
    switch (color_name) {
    case WindowsTerminalColor::BLACK: return cRGBi(0, 0, 0);
    case WindowsTerminalColor::BLUE: return cRGBi(0, 0, 128);
    case WindowsTerminalColor::GREEN: return cRGBi(0, 128, 0);
    case WindowsTerminalColor::CYAN: return cRGBi(0, 128, 128);
    case WindowsTerminalColor::RED: return cRGBi(128, 0, 0);
    case WindowsTerminalColor::MAGENTA: return cRGBi(128, 0, 128);
    case WindowsTerminalColor::YELLOW: return cRGBi(128, 128, 0);
    case WindowsTerminalColor::GRAY: return cRGBi(192, 192, 192);
    case WindowsTerminalColor::DARKGRAY: return cRGBi(128, 128, 128);
    case WindowsTerminalColor::LIGHT_BLUE: return cRGBi(0, 0, 255);
    case WindowsTerminalColor::LIGHT_GREEN: return cRGBi(0, 255, 0);
    case WindowsTerminalColor::LIGHT_CYAN: return cRGBi(0, 255, 255);
    case WindowsTerminalColor::LIGHT_RED: return cRGBi(255, 0, 0);
    case WindowsTerminalColor::LIGHT_MAGENTA: return cRGBi(255, 0, 255);
    case WindowsTerminalColor::LIGHT_YELLOW: return cRGBi(255, 255, 0);
    case WindowsTerminalColor::WHITE: return cRGBi(255, 255, 255);
    default: return cRGBi(0, 0, 0);
    }
  }

  static WindowsTerminalColor GetClosestWindowsTerminalColor(cRGBi color) {
    WindowsTerminalColor closest_color{ WindowsTerminalColor::BLACK };
    float closest_distance = std::numeric_limits<float>::infinity();
    for (auto c : Enum<WindowsTerminalColor>()) {
      float distance = color.distance(GetColor(c));
      if (distance < closest_distance) {
        closest_color = c;
        closest_distance = distance;
      }
    }
    return closest_color;
  }

  static cRGBi GetClosestColor(cRGBi color) { return GetColor(GetClosestWindowsTerminalColor(color)); }
};

} // namespace

#endif // ENGINE_COMMON_UTILITY_WINDOWSTERMINALCOLORS_H_