#pragma once

#include "./hashing_by_separate_chaining.hpp"
#include <cstddef>
#include <utility>

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
SeparateChaining<Key, Value, Bucket, Hash>::SeparateChaining() {
  hashTable.resize(10);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
SeparateChaining<Key, Value, Bucket, Hash>::SeparateChaining(
    const Key key, const Value value) {
  hashTable.resize(10);
  insert(key, value);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::insert(const Key key,
                                                        const Value value) {
  Bucket<Key, Value> item;
  item.insert(key, value);
  size_t index = Hash<Key>{}(key) % hashTable.size();
  hashTable.push_back(item);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::remove(const Key key) {}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
const Value &
SeparateChaining<Key, Value, Bucket, Hash>::find(const Key key) const {
  size_t index = Hash<Key>{}(key) % hashTable.size();
  return hashTable[index].find(key);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
bool SeparateChaining<Key, Value, Bucket, Hash>::isEmpty() const {
  return hashTable.empty();
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
std::size_t SeparateChaining<Key, Value, Bucket, Hash>::size() const {
  return hashTable.size();
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
std::size_t SeparateChaining<Key, Value, Bucket, Hash>::capacity() const {
  return hashTable.capacity();
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
std::size_t SeparateChaining<Key, Value, Bucket, Hash>::loadFactor() const {
  return 0; // Placeholder implementation
}