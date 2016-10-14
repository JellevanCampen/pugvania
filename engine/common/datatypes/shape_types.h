#pragma once
#ifndef ENGINE_COMMON_DATATYPES_SHAPETYPES_H_
#define ENGINE_COMMON_DATATYPES_SHAPETYPES_H_

#include <string>
#include <cmath>

namespace engine {

// Represents a direction and magnitude in 2D space. 
template<typename valuetype>
struct Vector2D {
public:
  // Constructors
  Vector2D() { }
  Vector2D(valuetype x, valuetype y) : x_(x), y_(y) { }

  // Operators
  inline bool operator== (const Vector2D& other) const { return (x_ == other.x_ && y_ == other.y_); }
  inline bool operator!= (const Vector2D& other) const { return (x_ != other.x_ || y_ != other.y_); }
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
  inline bool operator== (const Point2D& other) const { return (x_ == other.x_ && y_ == other.y_); }
  inline bool operator!= (const Point2D& other) const { return (x_ != other.x_ || y_ != other.y_); }
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
  inline Line2D operator+ () const { return Line2D<valuetype>(*this); }
  inline Line2D operator- () const { return Line2D<valuetype>(p2_, p1_); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  friend std::ostream& operator<<(std::ostream &os, const Line2D<valuetype>& line) { return os << "l(" << line.p1_ << ", " << line.p2_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
  inline valuetype Length() const { return p1_.Distance(p2_); }
  inline Vector2D<valuetype> Direction() const { return (p2_ - p1_); }
  inline Vector2D<valuetype> Normal() const { return (p2_ - p1_).Normal(); }

  Point2D<valuetype> p1_, p2_;
};
typedef Line2D<int> Line2Di, l2Di;
typedef Line2D<float> Line2Df, l2Df;
typedef Line2D<double> Line2Dd, l2Dd;

} // namespace

#endif // ENGINE_COMMON_DATATYPES_SHAPETYPES_H_