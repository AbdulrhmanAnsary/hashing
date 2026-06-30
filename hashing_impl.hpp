#pragma once

#include "./default_hash.hpp"
#include <cstddef>
#include <stdexcept>

template <class Key, class Value, class HashFunction = DefaultHash<Key>>
class Hashing {
private:
  std::vector<std::vector<Value>> hashTable;
  HashFunction hashFunction;
  std::size_t elementCount;

public:
  Hashing();
  virtual ~Hashing() = default;

  virtual void insert(const Key key, const Value value) = 0;
  virtual void remove(const Key key) = 0;
  virtual const Value &find(const Key key) const = 0;
  virtual bool isEmpty() const = 0;
  virtual std::size_t size() const = 0;
  virtual std::size_t capacity() const = 0;
  virtual std::size_t loadFactor() const = 0;

  const Value &operator[](Key key);
};

template <class Key, class Value, class HashFunction>
Hashing<Key, Value, HashFunction>::Hashing() {
  hashTable.resize(10);
  elementCount = 0;
}

template <class Key, class Value, class HashFunction>
void Hashing<Key, Value, HashFunction>::insert(const Key key,
                                               const Value value) {
  std::size_t index = hashFunction(key) % hashTable.size();
  hashTable[index].push_back(value);
  ++elementCount;
}

template <class Key, class Value, class HashFunction>
void Hashing<Key, Value, HashFunction>::remove(const Key key) {
  std::size_t index = hashFunction(key) % hashTable.size();
  elementCount -= hashTable[index].size();
  hashTable[index].clear();
}

template <class Key, class Value, class HashFunction>
bool Hashing<Key, Value, HashFunction>::isEmpty() const {
  return elementCount == 0;
}

template <class Key, class Value, class HashFunction>
std::size_t Hashing<Key, Value, HashFunction>::size() const {
  return elementCount;
}

template <class Key, class Value, class HashFunction>
std::size_t Hashing<Key, Value, HashFunction>::capacity() const {
  return hashTable.size();
}

template <class Key, class Value, class HashFunction>
std::size_t Hashing<Key, Value, HashFunction>::loadFactor() const {
  return capacity() == 0 ? 0 : (elementCount * 100) / capacity();
}

template <class Key, class Value, class HashFunction>
const Value &Hashing<Key, Value, HashFunction>::find(const Key key) const {
  std::size_t index = hashFunction(key) % hashTable.size();
  const auto &bucket = hashTable[index];
  if (bucket.empty()) {
    throw std::out_of_range("Key not found");
  }
  return bucket.front();
}

template <class Key, class Value, class HashFunction>
const Value &Hashing<Key, Value, HashFunction>::operator[](Key key) {
  return find(key);
}
