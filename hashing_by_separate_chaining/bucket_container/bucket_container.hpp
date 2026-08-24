#pragma once

#include <functional>
#include <utility>

template <class Key, class Value> class IBucket {
public:
  virtual ~IBucket() = default;

  virtual void insert(const Key &key, const Value &value) = 0;
  virtual void remove(const Key &key) = 0;
  virtual const Value &find(const Key &key) const = 0;
  const Value &operator[](const Key &key) const { return find(key); }
  virtual bool contains(const Key &key) const = 0;
  virtual bool isEmpty() const = 0;

  virtual void forEach(const std::function<void(const std::pair<Key, Value> &)>
                           &function) const = 0;
};