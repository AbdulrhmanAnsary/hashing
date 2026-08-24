#pragma once

#include <cstddef>
#include <functional>

template <class Key> struct DefaultSecondaryHash {
  std::size_t operator()(const Key &key, std::size_t capacity,
                         std::size_t prime) const {
    const std::size_t hash = std::hash<Key>{}(key);

    return prime - (hash % prime);
  }
};