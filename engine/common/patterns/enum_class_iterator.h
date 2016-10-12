#pragma once
#ifndef ENGINE_COMMON_PATTERNS_ENUMCLASSITERATOR_H_
#define ENGINE_COMMON_PATTERNS_ENUMCLASSITERATOR_H_

namespace engine {

// An iterator for enum classes, allowing for iteration of enum class 
// members using range-based loops. (Based on: 
// http://stackoverflow.com/questions/8498300/allow-for-range-based-for-with-enum-classes.)
// e.g. for (auto e : Enum<EnumName>())
template<typename T>
class Enum {
 public:
  class Iterator {
   public:
    Iterator(int value) : value_(value) { }
    T operator*() const { return (T)value_; }
    void operator++() { value_++; }
    bool operator!=(Iterator other) { return value_ != other.value_; }
   private:
    int value_;
  };
};

template<typename T>
typename Enum<T>::Iterator begin(Enum<T>) { return typename Enum<T>::Iterator(int(T::First)); }

template<typename T>
typename Enum<T>::Iterator end(Enum<T>) { return typename Enum<T>::Iterator(int(T::Last) + 1); }

} // namespace

#endif // ENGINE_COMMON_PATTERNS_ENUMCLASSITERATOR_H_