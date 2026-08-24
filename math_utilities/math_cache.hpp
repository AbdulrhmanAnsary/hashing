#pragma once

#include <cstddef>
#include <unordered_map>

template <class Key, class Value> class MathCache {
private:
  std::unordered_map<Key, Value> cache;

public:
  bool contains(const Key &key) const { return cache.find(key) != cache.end(); }

  const Value &get(const Key &key) const { return cache.at(key); }

  void put(const Key &key, const Value &value) {
    cache.insert_or_assign(key, value);
  }

  std::size_t size() const noexcept { return cache.size(); }

  void clear() noexcept { cache.clear(); }
};