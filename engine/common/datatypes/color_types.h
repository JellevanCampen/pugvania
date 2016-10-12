#pragma once
#ifndef ENGINE_COMMON_DATATYPES_COLORTYPES_H_
#define ENGINE_COMMON_DATATYPES_COLORTYPES_H_

#include <algorithm>

namespace engine {

// Represents a Red, Green, Blue (RGB) color, with components stored as 
// integer values. 
template <typename valuetype>
struct colorRGBinteger {
 public:
  // Constructors
  colorRGBinteger(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBinteger(valuetype r, valuetype g, valuetype b) : r_(r), g_(g), b_(b) { }

  // Casts
  inline operator colorRGBAi() const { return colorRGBAi(r_, g_, b_, valuetype(255)); }

  // Operators
  inline colorRGBinteger operator+ (const colorRGBinteger& other) const { return colorRGBinteger(std::min(r_ + other.r_, valuetype(255)), std::min(g_ + other.g_, valuetype(255)), std::min(b_ + other.b_, valuetype(255))); }
  inline colorRGBinteger operator- (const colorRGBinteger& other) const { return colorRGBinteger(r_>other.r_ ? r_ - other.r_ : valuetype(0), g_>other.g_ ? g_ - other.g_ : valuetype(0), b_>other.b_ ? b_ - other.b_ : valuetype(0)); }
  inline colorRGBinteger operator* (valuetype scalar) const { return colorRGBinteger(std::min(r_ * scalar, valuetype(255)), std::min(g_ * scalar, valuetype(255)), std::min(b_ * scalar, valuetype(255))); }
  inline colorRGBinteger operator* (float scalar) const { return colorRGBinteger(std::min(int(r_ * scalar), valuetype(255)), std::min(int(g_ * scalar), valuetype(255)), std::min(int(b_ * scalar), valuetype(255))); }
  inline colorRGBinteger operator/ (valuetype scalar) const { return colorRGBinteger(std::min(r_ / scalar, valuetype(255)), std::min(g_ / scalar, valuetype(255)), std::min(b_ / scalar, valuetype(255))); }
  inline colorRGBinteger operator/ (float scalar) const { return colorRGBinteger(std::min(int(r_ / scalar), valuetype(255)), std::min(int(g_ / scalar), valuetype(255)), std::min(int(b_ / scalar), valuetype(255))); }

  valuetype r_{ valuetype(0) }, g_{ valuetype(0) }, b_{ valuetype(0) };
};
// TODO(Jelle): test whether there are no over- or underflow problems. If so only the unsigned char version should be needed
typedef colorRGBinteger<unsigned int> cRGBi;
typedef colorRGBinteger<unsigned short> cRGBs;
typedef colorRGBinteger<unsigned char> cRGBc;

// Represents a Red, Green, Blue, Alpha (RGBA) color, with components stored 
// as integer values. 
template <typename valuetype>
struct colorRGBAinteger {
 public: 
  // Constructors
  colorRGBAinteger(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBAinteger(valuetype r, valuetype g, valuetype b, valuetype a = valuetype(255)) : r_(r), g_(g), b_(b), a_(a) { }
   
  // Casts
  inline operator colorRGBAinteger() const { return colorRGBAinteger(r_, g_, b_); }

  // Operators
  inline colorRGBAinteger operator+ (const colorRGBAinteger& other) const { return colorRGBAinteger(std::min(r_ + other.r_, valuetype(255)), std::min(g_ + other.g_, valuetype(255)), std::min(b_ + other.b_, valuetype(255)), a_); }
  inline colorRGBAinteger operator- (const colorRGBAinteger& other) const { return colorRGBAinteger(r_>other.r_ ? r_-other.r_ : valuetype(0), g_>other.g_ ? g_ - other.g_ : valuetype(0), b_>other.b_ ? b_ - other.b_ : valuetype(0), a_); }
  inline colorRGBAinteger operator* (valuetype scalar) const { return colorRGBAinteger(std::min(r_ * scalar, valuetype(255)), std::min(g_ * scalar, valuetype(255)), std::min(b_ * scalar, valuetype(255)), a_); }
  inline colorRGBAinteger operator* (float scalar) const { return colorRGBAinteger(std::min(int(r_ * scalar), valuetype(255)), std::min(int(g_ * scalar), valuetype(255)), std::min(int(b_ * scalar), valuetype(255)), a_); }
  inline colorRGBAinteger operator/ (valuetype scalar) const { return colorRGBAinteger(std::min(r_ / scalar, valuetype(255)), std::min(g_ / scalar, valuetype(255)), std::min(b_ / scalar, valuetype(255)), a_); }
  inline colorRGBAinteger operator/ (float scalar) const { return colorRGBAinteger(std::min(int(r_ / scalar), valuetype(255)), std::min(int(g_ / scalar), valuetype(255)), std::min(int(b_ / scalar), valuetype(255)), a_); }

  valuetype r_{ valuetype(0) }, g_{ valuetype(0) }, b_{ valuetype(0) }, a_{ valuetype(255) };
};
// TODO(Jelle): test whether there are no over- or underflow problems. If so only the unsigned char version should be needed
typedef colorRGBAinteger<unsigned int> cRGBAi;
typedef colorRGBAinteger<unsigned short> cRGBAs;
typedef colorRGBAinteger<unsigned char> cRGBAc;

// TODO(Jelle): implement float versions of these as well as casting operators. 
// Note that float ranges vary from 0.0f to 1.0f and not 0 to 255

} // namespace

#endif // ENGINE_COMMON_DATATYPES_COLORTYPES_H_