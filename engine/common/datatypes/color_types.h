#pragma once
#ifndef ENGINE_COMMON_DATATYPES_COLORTYPES_H_
#define ENGINE_COMMON_DATATYPES_COLORTYPES_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace engine {

// Represents a Red, Green, Blue (RGB) color, with components stored as 
// integer values. 
template <typename valuetype>
struct colorRGBinteger {
 public:
  // Constructors
  colorRGBinteger(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBinteger(valuetype r, valuetype g, valuetype b) : r_(r), g_(g), b_(b) { }
  colorRGBinteger(std::string color_string) { 
    std::stringstream color_ss{ color_string };
    std::string value_s;
    int value_i;
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    r_ = valuetype(value_i);
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    g_ = valuetype(value_i);
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    b_ = valuetype(value_i);
  }

  // Operators
  inline colorRGBinteger operator+ (const colorRGBinteger& other) const { return colorRGBinteger(unsigned int(r_) + unsigned int(other.r_) > 255u ? valuetype(255) : valuetype(r_ + other.r_), unsigned int(g_) + unsigned int(other.g_) > 255u ? valuetype(255) : valuetype(g_ + other.g_), unsigned int(b_) + unsigned int(other.b_) > 255u ? valuetype(255) : valuetype(b_ + other.b_)); }
  inline colorRGBinteger operator- (const colorRGBinteger& other) const { return colorRGBinteger(r_>other.r_ ? r_ - other.r_ : valuetype(0), g_>other.g_ ? g_ - other.g_ : valuetype(0), b_>other.b_ ? b_ - other.b_ : valuetype(0)); }
  inline colorRGBinteger operator* (float scalar) const { return colorRGBinteger(unsigned int(0.5f + r_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + r_ * scalar), unsigned int(0.5f + g_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + g_ * scalar), unsigned int(0.5f + b_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + b_ * scalar)); }
  inline colorRGBinteger operator/ (float scalar) const { return colorRGBinteger(unsigned int(0.5f + r_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + r_ / scalar), unsigned int(0.5f + g_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + g_ / scalar), unsigned int(0.5f + b_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + b_ / scalar)); }
  friend std::ostream& operator<<(std::ostream &os, colorRGBinteger const &c) { return os << "(" << unsigned int(c.r_) << ", " << unsigned int(c.g_) << ", " << unsigned int(c.b_) << ")"; }

  valuetype r_{ valuetype(0) }, g_{ valuetype(0) }, b_{ valuetype(0) };
};
typedef colorRGBinteger<unsigned char> cRGBi;

// Represents a Red, Green, Blue, Alpha (RGBA) color, with components stored 
// as integer values. 
template <typename valuetype>
struct colorRGBAinteger {
 public: 
  // Constructors
  colorRGBAinteger(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBAinteger(valuetype r, valuetype g, valuetype b, valuetype a = valuetype(255)) : r_(r), g_(g), b_(b), a_(a) { }
  colorRGBAinteger(std::string color_string) {
    std::stringstream color_ss{ color_string };
    std::string value_s;
    int value_i;
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    r_ = valuetype(value_i);
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    g_ = valuetype(value_i);
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    b_ = valuetype(value_i);
    std::getline(color_ss, value_s, ',');
    value_i = std::stoi(value_s.c_str());
    value_i = value_i < 0 ? 0 : (value_i > 255 ? 255 : value_i);
    a_ = valuetype(value_i);
  }
  template <typename cast_valuetype> colorRGBAinteger(const colorRGBinteger<cast_valuetype>& c) : r_(valuetype(c.r_)), g_(valuetype(c.g_)), b_(valuetype(c.b_)) { }
   
  // Casts
  template<typename cast_valuetype> inline operator colorRGBinteger<cast_valuetype>() const { return colorRGBinteger<cast_valuetype>(cast_valuetype(r_), cast_valuetype(g_), cast_valuetype(b_)); }

  // Operators
  inline colorRGBAinteger operator+ (const colorRGBAinteger& other) const { return colorRGBAinteger(unsigned int(r_) + unsigned int(other.r_) > 255u ? valuetype(255) : valuetype(r_ + other.r_), unsigned int(g_) + unsigned int(other.g_) > 255u ? valuetype(255) : valuetype(g_ + other.g_), unsigned int(b_) + unsigned int(other.b_) > 255u ? valuetype(255) : valuetype(b_ + other.b_), unsigned int(a_) + unsigned int(other.a_) > 255u ? valuetype(255) : valuetype(a_ + other.a_)); }
  inline colorRGBAinteger operator- (const colorRGBAinteger& other) const { return colorRGBAinteger(r_>other.r_ ? r_-other.r_ : valuetype(0), g_>other.g_ ? g_ - other.g_ : valuetype(0), b_>other.b_ ? b_ - other.b_ : valuetype(0), a_); }
  inline colorRGBAinteger operator* (float scalar) const { return colorRGBAinteger(unsigned int(0.5f + r_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + r_ * scalar), unsigned int(0.5f + g_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + g_ * scalar), unsigned int(0.5f + b_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + b_ * scalar), unsigned int(0.5f + a_ * scalar) > 255 ? valuetype(255) : valuetype(0.5f + a_ * scalar)); }
  inline colorRGBAinteger operator/ (float scalar) const { return colorRGBAinteger(unsigned int(0.5f + r_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + r_ / scalar), unsigned int(0.5f + g_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + g_ / scalar), unsigned int(0.5f + b_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + b_ / scalar), unsigned int(0.5f + a_ / scalar) > 255 ? valuetype(255) : valuetype(0.5f + a_ / scalar)); }
  friend std::ostream& operator<<(std::ostream &os, colorRGBAinteger const &c) { return os << "(" << unsigned int(c.r_) << ", " << unsigned int(c.g_) << ", " << unsigned int(c.b_) << ", " << unsigned int(c.a_) << ")"; }

  valuetype r_{ valuetype(0) }, g_{ valuetype(0) }, b_{ valuetype(0) }, a_{ valuetype(255) };
};
typedef colorRGBAinteger<unsigned char> cRGBAi;

// Represents a Red, Green, Blue (RGB) color, with components stored as 
// float values. 
template <typename valuetype>
struct colorRGBfloat {
public:
  // Constructors
  colorRGBfloat(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBfloat(valuetype r, valuetype g, valuetype b) : r_(r), g_(g), b_(b) { }
  colorRGBfloat(std::string color_string) {
    std::stringstream color_ss{ color_string };
    std::string value_s;
    float value_f;
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    r_ = valuetype(value_f);
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    g_ = valuetype(value_f);
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    b_ = valuetype(value_f);
  }
  template <typename cast_valuetype> colorRGBfloat(const colorRGBinteger<cast_valuetype>& c) : r_(valuetype(c.r_) / valuetype(255.0)), g_(valuetype(c.g_) / valuetype(255.0)), b_(valuetype(c.b_) / valuetype(255.0)) { }
  template <typename cast_valuetype> colorRGBfloat(const colorRGBAinteger<cast_valuetype>& c) : r_(valuetype(c.r_) / valuetype(255.0)), g_(valuetype(c.g_) / valuetype(255.0)), b_(valuetype(c.b_) / valuetype(255.0)) { }

  // Casts
  template<typename cast_valuetype> inline operator colorRGBinteger<cast_valuetype>() const { return colorRGBinteger<cast_valuetype>(cast_valuetype(valuetype(0.5) + r_ * valuetype(255.0)) , cast_valuetype(valuetype(0.5) + g_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + b_ * valuetype(255.0))); }
  template<typename cast_valuetype> inline operator colorRGBAinteger<cast_valuetype>() const { return colorRGBAinteger<cast_valuetype>(cast_valuetype(valuetype(0.5) + r_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + g_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + b_ * valuetype(255.0))); }

  // Operators
  inline colorRGBfloat operator+ (const colorRGBfloat& other) const { return colorRGBfloat(std::min(r_ + other.r_, valuetype(1.0)), std::min(g_ + other.g_, valuetype(1.0)), std::min(b_ + other.b_, valuetype(1.0))); }
  inline colorRGBfloat operator- (const colorRGBfloat& other) const { return colorRGBfloat(r_>other.r_ ? r_ - other.r_ : valuetype(0.0), g_>other.g_ ? g_ - other.g_ : valuetype(0.0), b_>other.b_ ? b_ - other.b_ : valuetype(0.0)); }
  inline colorRGBfloat operator* (valuetype scalar) const { return colorRGBfloat(std::min(r_ * scalar, valuetype(1.0)), std::min(g_ * scalar, valuetype(1.0)), std::min(b_ * scalar, valuetype(1.0))); }
  inline colorRGBfloat operator/ (valuetype scalar) const { return colorRGBfloat(std::min(r_ / scalar, valuetype(1.0)), std::min(g_ / scalar, valuetype(1.0)), std::min(b_ / scalar, valuetype(1.0))); }
  friend std::ostream& operator<<(std::ostream &os, colorRGBfloat const &c) { return os << "(" << c.r_ << ", " << c.g_ << ", " << c.b_ << ")"; }

  valuetype r_{ valuetype(0.0) }, g_{ valuetype(0.0) }, b_{ valuetype(0.0) };
};
typedef colorRGBfloat<float> cRGBf;
typedef colorRGBfloat<double> cRGBd;

// Represents a Red, Green, Blue, Alpha (RGBA) color, with components stored 
// as float values. 
template <typename valuetype>
struct colorRGBAfloat {
public:
  // Constructors
  colorRGBAfloat(valuetype v) : r_(v), g_(v), b_(v) { }
  colorRGBAfloat(valuetype r, valuetype g, valuetype b, valuetype a = valuetype(1.0)) : r_(r), g_(g), b_(b), a_(a) { }
  colorRGBAfloat(std::string color_string) {
    std::stringstream color_ss{ color_string };
    std::string value_s;
    float value_f;
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    r_ = valuetype(value_f);
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    g_ = valuetype(value_f);
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    b_ = valuetype(value_f);
    std::getline(color_ss, value_s, ',');
    value_f = std::stof(value_s.c_str());
    value_f = value_f < 0.0f ? 0.0f : (value_f > 1.0f ? 1.0f : value_f);
    a_ = valuetype(value_f);
  }
  template <typename cast_valuetype> colorRGBAfloat(const colorRGBinteger<cast_valuetype>& c) : r_(valuetype(c.r_) / valuetype(255.0)), g_(valuetype(c.g_) / valuetype(255.0)), b_(valuetype(c.b_) / valuetype(255.0)) { }
  template <typename cast_valuetype> colorRGBAfloat(const colorRGBAinteger<cast_valuetype>& c) : r_(valuetype(c.r_) / valuetype(255.0)), g_(valuetype(c.g_) / valuetype(255.0)), b_(valuetype(c.b_) / valuetype(255.0)), a_(valuetype(c.a_) / valuetype(255.0)) { }
  template <typename cast_valuetype> colorRGBAfloat(const colorRGBfloat<cast_valuetype>& c) : r_(valuetype(c.r_)), g_(valuetype(c.g_)), b_(valuetype(c.b_)) { }

  // Casts
  template<typename cast_valuetype> inline operator colorRGBinteger<cast_valuetype>() const { return colorRGBinteger<cast_valuetype>(cast_valuetype(valuetype(0.5) + r_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + g_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + b_ * valuetype(255.0))); }
  template<typename cast_valuetype> inline operator colorRGBAinteger<cast_valuetype>() const { return colorRGBAinteger<cast_valuetype>(cast_valuetype(valuetype(0.5) + r_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + g_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + b_ * valuetype(255.0)), cast_valuetype(valuetype(0.5) + a_ * valuetype(255.0))); }
  template<typename cast_valuetype> inline operator colorRGBfloat<cast_valuetype>() const { return colorRGBfloat<cast_valuetype>(cast_valuetype(r_), cast_valuetype(g_), cast_valuetype(b_)); }

  // Operators
  inline colorRGBAfloat operator+ (const colorRGBAfloat& other) const { return colorRGBAfloat(std::min(r_ + other.r_, valuetype(1.0)), std::min(g_ + other.g_, valuetype(1.0)), std::min(b_ + other.b_, valuetype(1.0)), std::min(a_ + other.a_, valuetype(1.0))); }
  inline colorRGBAfloat operator- (const colorRGBAfloat& other) const { return colorRGBAfloat(r_>other.r_ ? r_ - other.r_ : valuetype(0.0), g_>other.g_ ? g_ - other.g_ : valuetype(0.0), b_>other.b_ ? b_ - other.b_ : valuetype(0.0), a_>other.a_ ? a_ - other.a_ : valuetype(0.0)); }
  inline colorRGBAfloat operator* (valuetype scalar) const { return colorRGBAfloat(std::min(r_ * scalar, valuetype(1.0)), std::min(g_ * scalar, valuetype(1.0)), std::min(b_ * scalar, valuetype(1.0)), std::min(a_ * scalar, valuetype(1.0))); }
  inline colorRGBAfloat operator/ (valuetype scalar) const { return colorRGBAfloat(std::min(r_ / scalar, valuetype(1.0)), std::min(g_ / scalar, valuetype(1.0)), std::min(b_ / scalar, valuetype(1.0)), std::min(a_ / scalar, valuetype(1.0))); }
  friend std::ostream& operator<<(std::ostream &os, colorRGBAfloat const &c) { return os << "(" << c.r_ << ", " << c.g_ << ", " << c.b_ << ", " << c.a_ << ")"; }

  valuetype r_{ valuetype(0.0) }, g_{ valuetype(0.0) }, b_{ valuetype(0.0) }, a_{ valuetype(1.0) };
};
typedef colorRGBAfloat<float> cRGBAf;
typedef colorRGBAfloat<double> cRGBAd;

} // namespace

#endif // ENGINE_COMMON_DATATYPES_COLORTYPES_H_