#pragma once

#include "./default_hash.hpp"
#include <cstddef>

template <class Key, class Value, template <class> class Hash = DefaultHash>
class IHashing {
protected:
  Hash<Key> hashFunction;

public:
  virtual ~IHashing() = default;

  virtual void insert(const Key &key, const Value &value) = 0;
  virtual void insert(const std::pair<Key, Value> &entry) = 0;
  virtual void remove(const Key &key) = 0;
  virtual void rehash(std::size_t newCapacity) = 0;
  virtual void reserve(std::size_t expectedItems) = 0;
  virtual const Value &find(const Key &key) const = 0;
  virtual bool contains(const Key &key) const = 0;
  virtual bool isEmpty() const = 0;
  virtual std::size_t size() const = 0;
  virtual std::size_t capacity() const = 0;
  virtual double getLoadFactor(int itemDelta = 0) const = 0;

  const Value &operator[](Key &key) { return find(key); }
};