#pragma once
#ifndef ENGINE_COMMON_DATATYPES_SHAPETYPES_H_
#define ENGINE_COMMON_DATATYPES_SHAPETYPES_H_

#include <string>

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

  inline Vector2D SwizzleYX() const { return Vector2D(y_, x_); }
  inline valuetype Length() const { return std::sqrtf((*this) * (*this)); }
  inline Vector2D Normalize() const { return (*this) / Length(); }
  inline valuetype ScalarProduct(const Vector2D& other) const { return (*this) * other; }
  inline Vector2D Project(const Vector2D& other) const { return other * ((*this) * other) / (other * other); }
  inline Vector2D Reflect(const Vector2D& normal) const { return (*this) - (Project(normal) * valuetype(2.0)); }

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
  inline Vector2D<valuetype> operator- (const Point2D<valuetype>& other) const { return Vector2D<valuetype>(other.x_ - x_, other.y_ - y_); }
  inline void operator+= (const Vector2D<valuetype>& vector) { Move(vector); }
  inline void operator-= (const Vector2D<valuetype>& vector) { Move(-vector); }
  friend std::ostream& operator<<(std::ostream &os, const Point2D& point) { return os << "p(" << point.x_ << ", " << point.y_ << ")"; }

  inline void Move(const Vector2D<valuetype>& vector) { x_ += vector.x_; y_ += vector.y_; }
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

} // namespace

#endif // ENGINE_COMMON_DATATYPES_SHAPETYPES_H_