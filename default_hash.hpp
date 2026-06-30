#pragma once

#include <cstddef>
#include <functional>

template <class Key> struct DefaultHash {
  std::size_t operator()(const Key key) const { return std::hash<Key>{}(key); }
};
