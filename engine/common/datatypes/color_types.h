#pragma once
#ifndef ENGINE_COMMON_DATATYPES_COLORTYPES_H_
#define ENGINE_COMMON_DATATYPES_COLORTYPES_H_

#include <algorithm>

namespace engine {

// Represents a Red, Green, Blue (RGB) color, with components stored as 
// integer values. 
struct colorRGBi {
 public:
  // Constructors
  colorRGBi(unsigned short int v) : r_(v), g_(v), b_(v) { }
  colorRGBi(unsigned short int r, unsigned short int g, unsigned short int b) : r_(r), g_(g), b_(b) { }

  // Casts
  inline operator colorRGBAi() const { return colorRGBAi(r_, g_, b_, 255); }

  // Operators
  inline colorRGBi operator+ (const colorRGBi& other) const { return colorRGBi(std::min(r_ + other.r_, 255), std::min(g_ + other.g_, 255), std::min(b_ + other.b_, 255)); }
  inline colorRGBi operator- (const colorRGBi& other) const { return colorRGBi(r_>other.r_ ? r_ - other.r_ : 0, g_>other.g_ ? g_ - other.g_ : 0, b_>other.b_ ? b_ - other.b_ : 0); }
  inline colorRGBi operator* (unsigned short int scalar) const { return colorRGBi(std::min(r_ * scalar, 255), std::min(g_ * scalar, 255), std::min(b_ * scalar, 255)); }
  inline colorRGBi operator* (float scalar) const { return colorRGBi(std::min(int(r_ * scalar), 255), std::min(int(g_ * scalar), 255), std::min(int(b_ * scalar), 255)); }
  inline colorRGBi operator/ (unsigned short int scalar) const { return colorRGBi(std::min(r_ / scalar, 255), std::min(g_ / scalar, 255), std::min(b_ / scalar, 255)); }
  inline colorRGBi operator/ (float scalar) const { return colorRGBi(std::min(int(r_ / scalar), 255), std::min(int(g_ / scalar), 255), std::min(int(b_ / scalar), 255)); }

  unsigned short int r_{ 0 }, g_{ 0 }, b_{ 0 };
};
typedef colorRGBi cRGBi;

// Represents a Red, Green, Blue, Alpha (RGBA) color, with components stored 
// as integer values. 
struct colorRGBAi {
 public: 
  // Constructors
  colorRGBAi(unsigned short int v) : r_(v), g_(v), b_(v) { }
  colorRGBAi(unsigned short int r, unsigned short int g, unsigned short int b, unsigned short int a = 255) : r_(r), g_(g), b_(b), a_(a) { }
   
  // Casts
  inline operator colorRGBi() const { return colorRGBi(r_, g_, b_); }

  // Operators
  inline colorRGBAi operator+ (const colorRGBAi& other) const { return colorRGBAi(std::min(r_ + other.r_, 255), std::min(g_ + other.g_, 255), std::min(b_ + other.b_, 255), a_); }
  inline colorRGBAi operator- (const colorRGBAi& other) const { return colorRGBAi(r_>other.r_ ? r_-other.r_ : 0, g_>other.g_ ? g_ - other.g_ : 0, b_>other.b_ ? b_ - other.b_ : 0, a_); }
  inline colorRGBAi operator* (unsigned short int scalar) const { return colorRGBAi(std::min(r_ * scalar, 255), std::min(g_ * scalar, 255), std::min(b_ * scalar, 255), a_); }
  inline colorRGBAi operator* (float scalar) const { return colorRGBAi(std::min(int(r_ * scalar), 255), std::min(int(g_ * scalar), 255), std::min(int(b_ * scalar), 255), a_); }
  inline colorRGBAi operator/ (unsigned short int scalar) const { return colorRGBAi(std::min(r_ / scalar, 255), std::min(g_ / scalar, 255), std::min(b_ / scalar, 255), a_); }
  inline colorRGBAi operator/ (float scalar) const { return colorRGBAi(std::min(int(r_ / scalar), 255), std::min(int(g_ / scalar), 255), std::min(int(b_ / scalar), 255), a_); }

  unsigned short int r_{ 0 }, g_{ 0 }, b_{ 0 }, a_{ 255 };
};
typedef colorRGBAi cRGBAi;

// TODO(Jelle): implement float versions of these as well as casting operators. 
// Note that float ranges vary from 0.0f to 1.0f and not 0 to 255

} // namespace

#endif // ENGINE_COMMON_DATATYPES_COLORTYPES_H_