#pragma once
#ifndef ENGINE_COMMON_DATATYPES_SHAPETYPES_H_
#define ENGINE_COMMON_DATATYPES_SHAPETYPES_H_

#include <string>
#include <cmath>
#include "common\utility\float_comparison.h"

namespace engine {

// Represents a direction and magnitude in 2D space. 
template<typename valuetype>
struct Vector2D {
public:
  // Constructors
  Vector2D() { }
  Vector2D(valuetype x, valuetype y) : x_(x), y_(y) { }

  // Operators
  inline bool operator== (const Vector2D& other) const { return (FloatComparison::AreEqual(x_, other.x_) && FloatComparison::AreEqual(y_, other.y_)); }
  inline bool operator!= (const Vector2D& other) const { return (!FloatComparison::AreEqual(x_, other.x_) || !FloatComparison::AreEqual(y_, other.y_)); }
  inline Vector2D operator+ () const { return Vector2D(*this); }
  inline Vector2D operator- () const { return Vector2D(-x_, -y_); }
  inline Vector2D operator+ (const Vector2D& other) const { return Vector2D(x_ + other.x_, y_ + other.y_); }
  inline Vector2D operator- (const Vector2D& other) const { return Vector2D(x_ - other.x_, y_ - other.y_); }
  inline Vector2D operator* (valuetype scalar) const { return Vector2D(x_ * scalar, y_ * scalar); }
  inline valuetype operator* (const Vector2D& other) const { return x_ * other.x_ + y_ * other.y_; }
  inline Vector2D operator/ (valuetype scalar) const { return Vector2D(x_ / scalar, y_ / scalar); }
  inline void operator+= (const Vector2D& other) { x_ += other.x_; y_ += other.y_; }
  inline void operator-= (const Vector2D& vector) { x_ -= other.x_; y_ -= other.y_; }
  inline void operator*= (valuetype scalar) { x_ *= scalar; y_ *= scalar; }
  inline void operator/= (valuetype scalar) { x_ /= scalar; y_ /= scalar; }
  friend std::ostream& operator<<(std::ostream &os, const Vector2D& vector) { return os << "v(" << vector.x_ << ", " << vector.y_ << ")"; }

  inline valuetype Length() const { return std::sqrtf((*this) * (*this)); }
  inline Vector2D Normalize() const { return (*this) / Length(); }
  inline Vector2D SwizzleYX() const { return Vector2D(y_, x_); }
  inline Vector2D Normal() const { return Vector2D(-y_, x_); }
  inline valuetype ScalarProduct(const Vector2D& other) const { return (*this) * other; }
  inline Vector2D Project(const Vector2D& other) const { return other * ((*this) * other) / (other * other); }
  inline Vector2D Reflect(const Vector2D& normal) const { return (*this) - (Project(normal) * valuetype(2.0)); }
  inline Vector2D Rotate(float angle_radians) const { return Vector2D(valuetype(float(x_) * std::cosf(angle_radians) - float(y_) * std::sinf(angle_radians)), valuetype(float(x_) * std::sinf(angle_radians) + float(y_) * std::cosf(angle_radians))); }

  valuetype x_{ valuetype(0) }, y_{ valuetype(0) };
};
typedef Vector2D<int> Vector2Di, vec2Di;
typedef Vector2D<float> Vector2Df, vec2Df;
typedef Vector2D<double> Vector2Dd, vec2Dd;

// Represents a point in 2D space. 
template<typename valuetype>
struct Point2D {
public:
  // Constructors
  Point2D() { }
  Point2D(valuetype x, valuetype y) : x_(x), y_(y) { }

  // Operators
  inline bool operator== (const Point2D& other) const { return (FloatComparison::AreEqual(x_, other.x_) && FloatComparison::AreEqual(y_, other.y_)); }
  inline bool operator!= (const Point2D& other) const { return (!FloatComparison::AreEqual(x_, other.x_) || !FloatComparison::AreEqual(y_, other.y_)); }
  inline Point2D operator+ (const Vector2D<valuetype>& vector) const { return Point2D(x_ + vector.x_, y_ + vector.y_); }
  inline Point2D operator- (const Vector2D<valuetype>& vector) const { return Point2D(x_ - vector.x_, y_ - vector.y_); }
  inline Vector2D<valuetype> operator- (const Point2D<valuetype>& other) const { return Vector2D<valuetype>(x_ - other.x_, y_ - other.y_); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  friend std::ostream& operator<<(std::ostream &os, const Point2D& point) { return os << "p(" << point.x_ << ", " << point.y_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { p1_ += vector; p2_ += vector; }
  float Distance(const Point2D& other) const {
    float dx = float(x_) - float(other.x_);
    float dy = float(y_) - float(other.y_);
    return std::sqrtf(dx * dx + dy * dy);
  }
  inline Point2D Interpolate(Point2D other, float amount) const { return Point2D(valuetype(x_ * (1.0f - amount) + other.x_ * amount), valuetype(y_ * (1.0f - amount) + other.y_ * amount)); }

  valuetype x_{ valuetype(0) }, y_{ valuetype(0) };
};
typedef Point2D<int> Point2Di, p2Di;
typedef Point2D<float> Point2Df, p2Df;
typedef Point2D<double> Point2Dd, p2Dd;

// Represents a line segment in 2D space. 
template<typename valuetype>
struct Line2D {
public:
  // Constructors
  Line2D() { }
  Line2D(Point2D<valuetype> p1, Point2D<valuetype> p2) : p1_(p1), p2_(p2) { }
  Line2D(valuetype x1, valuetype y1, valuetype x2, valuetype y2) : p1_(Point2D<valuetype>(x1, y1)), p2_(Point2D<valuetype>(x2, y2)) { }

  // Operators
  inline bool operator== (const Point2D<valuetype>& other) const { return (p1_ == other.p1_ && p2_ == other.p2_) || (p1_ == other.p2_ && p2_ == other.p1_); }
  inline bool operator!= (const Point2D<valuetype>& other) const { return !((*this) == other); }
  inline Line2D operator+ (const Vector2D<valuetype>& vector) const { return Line2D(p1_ + vector, p2_ + vector); }
  inline Line2D operator- (const Vector2D<valuetype>& vector) const { return Line2D(p1_ - vector, p2_ - vector); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  inline Point2D<valuetype> operator[] (float s) const { return PointOn(s); }
  friend std::ostream& operator<<(std::ostream &os, const Line2D<valuetype>& line) { return os << "l(" << line.p1_ << ", " << line.p2_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
  inline valuetype Length() const { return p1_.Distance(p2_); }
  inline Vector2D<valuetype> Direction() const { return (p2_ - p1_); }
  inline Vector2D<valuetype> Normal() const { return (p2_ - p1_).Normal(); }
  inline Point2D<valuetype> PointOn(float s) const { return p1_.Interpolate(p2_, s); }
  bool Contains(Point2D<valuetype> point) const { 
    bool on_line{ FloatComparison::AreEqual((p1_.x_ - p2_.x_) / (p1_.x_ - point.x_), (p1_.y_ - p2_.y_) / (p1_.y_ - point.y_)) };
    bool on_line_segment_x{ p1_.x_ <= p2_.x_ ? (p1_.x_ <= point.x_ && point.x_ <= p2_.x_) : (p2_.x_ <= point.x_ && point.x_ <= p1_.x_) };
    bool on_line_segment_y{ p1_.y_ <= p2_.y_ ? (p1_.y_ <= point.y_ && point.y_ <= p2_.y_) : (p2_.y_ <= point.y_ && point.y_ <= p1_.y_) };
    return on_line && on_line_segment_x && on_line_segment_y;
  }

  Point2D<valuetype> p1_, p2_;
};
typedef Line2D<int> Line2Di, l2Di;
typedef Line2D<float> Line2Df, l2Df;
typedef Line2D<double> Line2Dd, l2Dd;

// Represents an axis-aligned rectangle in 2D space. 
template<typename valuetype>
struct Rectangle2D {
public:
  // Constructors
  Rectangle2D() { }
  Rectangle2D(Point2D<valuetype> p1, Point2D<valuetype> p2) : p1_(p1), p2_(p2) { }
  Rectangle2D(valuetype x1, valuetype y1, valuetype x2, valuetype y2) : p1_(Point2D<valuetype>(x1, y1)), p2_(Point2D<valuetype>(x2, y2)) { }
  Rectangle2D(Line2D<valuetype> line) : p1_(line.p1_), p2_(line.p2_) { }

  // Operators
  inline bool operator== (const Rectangle2D<valuetype>& other) const { return (p1_ == other.p1_ && p2_ == other.p2_) || (p1_ == other.p2_ && p2_ == other.p1_); }
  inline bool operator!= (const Rectangle2D<valuetype>& other) const { return !((*this) == other); }
  inline Rectangle2D operator+ (const Vector2D<valuetype>& vector) const { return Rectangle2D(p1_ + vector, p2_ + vector); }
  inline Rectangle2D operator- (const Vector2D<valuetype>& vector) const { return Rectangle2D(p1_ - vector, p2_ - vector); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  inline Line2D<valuetype> operator[] (float s) const { return LineOn(s); }
  friend std::ostream& operator<<(std::ostream &os, const Rectangle2D<valuetype>& rectangle) { return os << "r(" << rectangle.p1_ << ", " << rectangle.p2_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { p1_ += vector; p2_ += vector; }
  inline Rectangle2D ReorderPoints() const {
    Point2D<valuetype> p1, p2;
    if (p1_.x_ <= p2_.x_) { p1.x_ = p1_.x_; p2.x_ = p2_.x_; }
    else { p1.x_ = p2_.x_; p2.x_ = p1_.x_; }
    if (p1_.y_ <= p2_.y_) { p1.y_ = p1_.y_; p2.y_ = p2_.y_; }
    else { p1.y_ = p2_.y_; p2.y_ = p1_.y_; }
    return Rectangle2D(p1, p2);
  }
  inline Vector2D<valuetype> Size() const { return Vector2D<valuetype>(valuetype(p1_.x_ <= p2_x_ ? p2_.x_ - p1.x_ : p1_.x_ - p2_.x_), valuetype(p1_.y_ <= p2_y_ ? p2_.y_ - p1.y_ : p1_.y_ - p2_.y_)); }
  inline valuetype Area() const { Vector2D<valuetype> size{ Size() }; return size.x_ * size.y_; }
  inline Line2D<valuetype> LineOn(float s) const {
    Rectangle2D r{ ReorderPoints() }; 
    valuetype x = r.p1_.x_ * (1.0f - s) + r.p2_.x_ * s;
    return Line2D<valuetype>(x, p1_.y_, x, p2_.y_); }
  inline Point2D<valuetype> PointOn(float s, float t) const { 
    Rectangle2D r{ ReorderPoints() }; 
    return Point2D<valuetype>(r.p1_.x_ * (1.0f - s) + r.p2_.x_ * s, r.p1_.t_ * (1.0f - t) + r.p2_.y_ * t); 
  }
  bool Contains(Point2D<valuetype> point) const {
    bool contains_x{ p1_.x_ <= p2_.x_ ? (p1_.x_ <= point.x_ && point.x_ <= p2_.x_) : (p2_.x_ <= point.x_ && point.x_ <= p1_.x_) };
    bool contains_y{ p1_.y_ <= p2_.y_ ? (p1_.y_ <= point.y_ && point.y_ <= p2_.y_) : (p2_.y_ <= point.y_ && point.y_ <= p1_.y_) };
    return contains_x && contains_y;
  }
  inline bool Contains(Line2D<valuetype> line) const { return Contains(line.p1_) && Contains(line.p2_); }

  Point2D<valuetype> p1_, p2_;
};
typedef Rectangle2D<int> Rectangle2Di, r2Di;
typedef Rectangle2D<float> Rectangle2Df, r2Df;
typedef Rectangle2D<double> Rectangle2Dd, r2Dd;

// Represents a circle in 2D space. 
template<typename valuetype>
struct Circle2D {
public:
  // Constructors
  Circle2D() { }
  Circle2D(Point2D<valuetype> center, valuetype radius) : p_(center), r_(radius) { }
  Circle2D(valuetype x1, valuetype y1, valuetype radius) : p_(Point2D<valuetype>(x1, y1)), r_(radius) { }
  Circle2D(Rectangle2D<valuetype> rectangle, bool circle_is_enclosing = true) {
    Rectangle2D<valuetype> r{ rectangle.ReorderPoints() };
    Vector2D<valuetype> s{ rectangle.Size() };
    p_ = r.p1_ + s / valuetype(2);
    if (circle_is_enclosing == true) // Circle encloses the rectangle
      r_ = std::sqrtf(s.x_ * s.x_ + s.y_ * s.y_);
    else // Rectangle encloses the circle
      r_ = s.x_ <= s.y_ ? s.x_ : s.y_;
  }

  // Operators
  inline bool operator== (const Circle2D<valuetype>& other) const { return (p_ == other.p_ && FloatComparison::AreEqual(r_, other.r_)); }
  inline bool operator!= (const Circle2D<valuetype>& other) const { return (FloatComparison::AreEqual(r_, other.r_) || p_ != other.p_); }
  inline Circle2D operator+ (const Vector2D<valuetype>& vector) const { return Circle2D(p_ + vector, r_); }
  inline Circle2D operator- (const Vector2D<valuetype>& vector) const { return Circle2D(p_ - vector, r_); }
  inline Circle2D operator* (valuetype scalar) const { return Circle2D(p_, r_ * scalar); }
  inline Circle2D operator/ (valuetype scalar) const { return Circle2D(p_, r_ / scalar); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  inline void operator*= (valuetype scalar) { r_ *= scalar; }
  inline void operator/= (valuetype scalar) { r_ /= scalar; }
  inline Line2D<valuetype> operator[] (float angle) const { return LineOn(angle); }
  friend std::ostream& operator<<(std::ostream &os, const Circle2D<valuetype>& circle) { return os << "c(" << circle.p_ << ", r=" << circle.r_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { p_ += vector; }
  inline void Resize(valuetype scalar) { r_ *= scalar; }
  // TODO(Jelle): implement the area function, as it needs the Pi constant defined.
  // inline valuetype Area() const { /* TODO */ }
  inline Line2D<valuetype> LineOn(float angle) const { return Line2D<valuetype>(p_.x_, p_.y_, valuetype(float(p_.x_) + std::cosf(angle_radians)), valuetype(float(p_.y_) + std::sinf(angle_radians))); }
  inline Point2D<valuetype> PointOn(float angle, float radius) const { return LineOn(angle)[radius]; }
  inline bool Contains(Point2D<valuetype> point) const { p_.Distance(point) <= r_; }
  inline bool Contains(Line2D<valuetype> line) const { return Contains(line.p1_) && Contains(line.p2_); }
  // TODO(Jelle): implement this function by checking all four corner points. 
  // inline bool Contains(Rectangle2D<valuetype> rectangle) const { /* TODO */ }

  Point2D<valuetype> p_;
  valuetype r_;
};
typedef Circle2D<int> Circle2Di, c2Di;
typedef Circle2D<float> Circle2Df, c2Df;
typedef Circle2D<double> Circle2Dd, c2Dd;

} // namespace

#endif // ENGINE_COMMON_DATATYPES_SHAPETYPES_H_