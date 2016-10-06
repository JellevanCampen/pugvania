#pragma once
#ifndef ENGINE_UTILITY_PATTERNS_REVERSEITERATOR_H_
#define ENGINE_UTILITY_PATTERNS_REVERSEITERATOR_H_

#include <iterator>

namespace engine {

// Creates a reversed version of an iteratable collection, allowing for 
// reverse iteration using range-based loops. (Based on: 
// http://stackoverflow.com/questions/21510091/forauto-i-c-is-there-a-short-way-to-do-it-in-reverse-direction.)
// e.g. for (auto i : reverse(c))
template<typename It>
class Range {
 public:
  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

 private:
  It begin_, end_;
};

template<typename ORange, typename OIt = decltype(std::begin(std::declval<ORange>())), typename It = std::reverse_iterator<OIt>>
Range<It> reverse(ORange && originalRange) {
  return Range<It>(It(std::end(originalRange)), It(std::begin(originalRange)));
}

} // namespace

#endif // ENGINE_UTILITY_PATTERNS_REVERSEITERATOR_H_