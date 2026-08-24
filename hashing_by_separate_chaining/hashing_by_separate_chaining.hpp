#pragma once

#include "../default_hash.hpp"
#include "../hashing.hpp"
#include "../math_utilities/math_cache.hpp"
#include "./bucket_container/bucket_linked_list.hpp"
#include <cstddef>
#include <vector>

template <class Key, class Value,
          template <class, class> class Bucket = BucketLinkedList,
          template <class> class Hash = DefaultHash>
class SeparateChaining : public IHashing<Key, Value, Hash> {
private:
  std::vector<Bucket<Key, Value>> hashTable;
  std::size_t itemCount = 0;
  mutable MathCache<std::size_t, std::size_t> probingCache;
  static constexpr double MAX_LOAD_FACTOR = 0.75;
  static constexpr double MIN_LOAD_FACTOR = 0.30;

public:
  SeparateChaining(std::size_t initialCapacity = 10);
  SeparateChaining(const Key &key, const Value &value,
                   std::size_t initialCapacity = 10);

  virtual void insert(const Key &key, const Value &value) override;
  virtual void insert(const std::pair<Key, Value> &entry) override;
  virtual void remove(const Key &key) override;
  virtual void rehash(std::size_t newCapacity) override;
  virtual void reserve(std::size_t expectedItems) override;
  virtual const Value &find(const Key &key) const override;
  virtual bool contains(const Key &key) const override;
  virtual bool isEmpty() const override;
  virtual std::size_t size() const override;
  virtual std::size_t capacity() const override;
  virtual double getLoadFactor(int itemDelta = 0) const override;
};

// Template definitions
#include "./hashing_by_separate_chaining_impl.hpp"