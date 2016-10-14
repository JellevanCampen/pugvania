#pragma once
#ifndef ENGINE_COMMON_UTILITY_FLOATCOMPARISON_H_
#define ENGINE_COMMON_UTILITY_FLOATCOMPARISON_H_

#include <limits>
#include <cmath>

namespace engine {

  // Utility function to compare float values based on epsilon distance.
  namespace FloatComparison {

    template<typename T>
    static bool AreEqual(T f1, T f2) { 
      return (std::fabs(f1 - f2) <= std::numeric_limits<T>::epsilon() * std::fmax(fabs(f1), fabs(f2)));
    }

  } // namespace

} // namespace

#endif // ENGINE_COMMON_UTILITY_FLOATCOMPARISON_H_