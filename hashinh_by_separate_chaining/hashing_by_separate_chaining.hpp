#pragma once

#include "../default_hash.hpp"
#include "../hashing.hpp"
#include "./bucket_container/bucket_linked_list.hpp"
#include <cstddef>
#include <vector>

template <class Key, class Value,
          template <class, class> class Bucket = BucketLinkedList,
          template <class> class Hash = DefaultHash>
class SeparateChaining : public IHashing<Key, Value, Hash> {
private:
  std::vector<Bucket<Key, Value>> hashTable;

public:
  SeparateChaining();
  SeparateChaining(const Key key, const Value value);

  virtual void insert(const Key key, const Value value) override;
  virtual void remove(const Key key) override;
  virtual const Value &find(const Key key) const override;
  virtual bool isEmpty() const override;
  virtual std::size_t size() const override;
  virtual std::size_t capacity() const override;
  virtual std::size_t loadFactor() const override;
};

// Template definitions
#include "./hashing_by_separate_chaining_impl.hpp"