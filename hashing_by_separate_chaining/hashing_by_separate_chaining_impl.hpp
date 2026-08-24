#pragma once

#include "../math_utilities/prime_utils.hpp"
#include "./hashing_by_separate_chaining.hpp"
#include <cstddef>

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
SeparateChaining<Key, Value, Bucket, Hash>::SeparateChaining(
    std::size_t initialCapacity) {
  rehash(initialCapacity);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
SeparateChaining<Key, Value, Bucket, Hash>::SeparateChaining(
    const Key &key, const Value &value, std::size_t initialCapacity) {
  rehash(initialCapacity);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::insert(const Key &key,
                                                        const Value &value) {

  std::size_t index = this->hashFunction(key) % hashTable.size();

  // 1. Reject duplicate key first.
  if (hashTable[index].contains(key)) {
    throw std::invalid_argument("'" + key + "'" + " Key already exists.");
  }

  // 2. Check whether inserting the new element requires rehashing.
  if (getLoadFactor(1) >= MAX_LOAD_FACTOR) {
    rehash(capacity() * 2);

    // 3. Capacity changed, so the old index is no longer valid.
    index = this->hashFunction(key) % hashTable.size();
  }

  // 4. Insert into the correct bucket.
  hashTable[index].insert(key, value);
  ++itemCount;
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::insert(
    const std::pair<Key, Value> &entry) {
  Key key = entry.first;
  Value value = entry.second;

  insert(key, value);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::remove(const Key &key) {
  std::size_t index = this->hashFunction(key) % hashTable.size();

  if (!hashTable[index].contains(key)) {
    throw std::out_of_range("'" + key + "'" + " Key not found.");
  }

  if (getLoadFactor(-1) < MIN_LOAD_FACTOR) {
    rehash(capacity() / 2);

    // Capacity changed, so the old index is no longer valid.
    index = this->hashFunction(key) % hashTable.size();
  }

  hashTable[index].remove(key);
  --itemCount;
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::rehash(
    std::size_t newCapacity) {
  std::size_t requiredCapacity = PrimeUtils::getPrimeNumber(
      newCapacity, this->probingCache, PrimeUtils::getNextPrimeNumber);

  auto oldTable = std::move(hashTable);

  hashTable = std::vector<Bucket<Key, Value>>(requiredCapacity);
  itemCount = 0;

  for (const auto &bucket : oldTable) {
    bucket.forEach(
        [this](const auto &entry) { insert(entry.first, entry.second); });
  }
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
void SeparateChaining<Key, Value, Bucket, Hash>::reserve(
    std::size_t expectedItems) {
  std::size_t requiredCapacity = PrimeUtils::getPrimeNumber(
      expectedItems / MAX_LOAD_FACTOR, this->probingCache,
      PrimeUtils::getNextPrimeNumber);

  if (requiredCapacity > capacity()) {
    rehash(requiredCapacity);
  }
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
const Value &
SeparateChaining<Key, Value, Bucket, Hash>::find(const Key &key) const {
  size_t index = this->hashFunction(key) % hashTable.size();

  return hashTable[index].find(key);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
bool SeparateChaining<Key, Value, Bucket, Hash>::contains(
    const Key &key) const {
  size_t index = this->hashFunction(key) % hashTable.size();

  return hashTable[index].contains(key);
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
bool SeparateChaining<Key, Value, Bucket, Hash>::isEmpty() const {
  return itemCount == 0;
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
std::size_t SeparateChaining<Key, Value, Bucket, Hash>::size() const {
  return itemCount;
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
std::size_t SeparateChaining<Key, Value, Bucket, Hash>::capacity() const {
  return hashTable.capacity();
}

template <class Key, class Value, template <class, class> class Bucket,
          template <class> class Hash>
double
SeparateChaining<Key, Value, Bucket, Hash>::getLoadFactor(int itemDelta) const {
  return static_cast<double>(size() + itemDelta) / capacity();
}