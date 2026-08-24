#pragma once

#include "../math_utilities/prime_utils.hpp"
#include "./hasing_by_open_addressing.hpp"
#include <cstddef>
#include <linux/stat.h>
#include <stdexcept>
#include <utility>
#include <vector>

template <class Key, class Value, template <class> class Hash>
OpenAddressing<Key, Value, Hash>::OpenAddressing(std::size_t initialCapacity) {
  rehash(initialCapacity);
}

template <class Key, class Value, template <class> class Hash>
OpenAddressing<Key, Value, Hash>::OpenAddressing(const Key &key,
                                                 const Value &value,
                                                 std::size_t initialCapacity) {
  rehash(initialCapacity);
}

template <class Key, class Value, template <class> class Hash>
void OpenAddressing<Key, Value, Hash>::insert(const Key &key,
                                              const Value &value) {
  std::size_t index = getProbeIndex(key, 0);

  // 1. Reject duplicate key first.
  if (hashTable[index].isOccupied() && hashTable[index].key == key) {
    throw std::invalid_argument("'" + key + "' Key already exists.");
  }

  // 2. Check whether inserting the new element requires rehashing.
  if (getLoadFactor(1) >= MAX_LOAD_FACTOR) {
    rehash(capacity() * 2);
  }

  // 3. Insert into the correct entry and reject duplicate key.
  for (std::size_t attempt = 0; attempt < hashTable.size(); attempt++) {
    index = getProbeIndex(key, attempt);

    if (hashTable[index].isOccupied() && hashTable[index].key == key) {
      throw std::invalid_argument("'" + key + "' Key already exists.");
    }

    if (hashTable[index].isNotOccupied()) {
      hashTable[index] = Entry(key, value, OpenAddressing::SlotState::Occupied);
      itemCount++;

      return;
    }
  }
}

template <class Key, class Value, template <class> class Hash>
void OpenAddressing<Key, Value, Hash>::insert(
    const std::pair<Key, Value> &entry) {
  Key key = entry.first;
  Value value = entry.second;

  insert(key, value);
}

template <class Key, class Value, template <class> class Hash>
void OpenAddressing<Key, Value, Hash>::remove(const Key &key) {
  std::size_t index = getProbeIndex(key, 0);

  if (hashTable[index].isEmpty()) {
    throw std::out_of_range("'" + key + "' Key not found.");
  }

  if (getLoadFactor(-1) < MIN_LOAD_FACTOR) {
    rehash(capacity() / 2);
  }

  for (std::size_t attempt = 0; attempt < hashTable.size(); attempt++) {
    index = getProbeIndex(key, attempt);

    if (hashTable[index].isEmpty()) {
      throw std::out_of_range("'" + key + "' Key not found.");
    }

    if (hashTable[index].isOccupied() && hashTable[index].key == key) {
      hashTable[index].state = SlotState::Delete;
      --itemCount;

      return;
    }
  }

  throw std::out_of_range("'" + key + "' Key not found.");
}

template <class Key, class Value, template <class> class Hash>
void OpenAddressing<Key, Value, Hash>::rehash(std::size_t newCapacity) {
  newCapacity = std::max(newCapacity, MIN_CAPACITY);
  std::size_t requiredCapacity = PrimeUtils::getPrimeNumber(
      newCapacity, this->probingCache, PrimeUtils::getNextPrimeNumber);

  auto oldTable = std::move(hashTable);

  hashTable = std::vector<Entry>(requiredCapacity);
  itemCount = 0;

  for (const auto &entry : oldTable) {
    if (entry.isOccupied()) {
      insert(entry.key, entry.value);
    }
  }
}

template <class Key, class Value, template <class> class Hash>
void OpenAddressing<Key, Value, Hash>::reserve(std::size_t expectedItems) {
  std::size_t requiredCapacity = PrimeUtils::getPrimeNumber(
      expectedItems / MAX_LOAD_FACTOR, this->probingCache,
      PrimeUtils::getNextPrimeNumber);

  if (requiredCapacity > capacity()) {
    rehash(requiredCapacity);
  }
}

template <class Key, class Value, template <class> class Hash>
const Value &OpenAddressing<Key, Value, Hash>::find(const Key &key) const {
  for (std::size_t attempt = 0; attempt < hashTable.size(); attempt++) {
    std::size_t index = getProbeIndex(key, attempt);

    if (hashTable[index].isEmpty()) {
      throw std::out_of_range("'" + key + "' Key not found.");
    }

    if (hashTable[index].isOccupied() && hashTable[index].key == key) {
      return hashTable[index].value;
    }
  }

  throw std::out_of_range("'" + key + "' Key not found.");
}

template <class Key, class Value, template <class> class Hash>
bool OpenAddressing<Key, Value, Hash>::contains(const Key &key) const {
  for (std::size_t attempt = 0; attempt < hashTable.size(); attempt++) {
    std::size_t index = getProbeIndex(key, attempt);

    if (hashTable[index].isEmpty()) {
      return false;
    }

    if (hashTable[index].isOccupied() && hashTable[index].key == key) {
      return true;
    }
  }

  return false;
}

template <class Key, class Value, template <class> class Hash>
std::size_t
OpenAddressing<Key, Value, Hash>::getProbeIndex(const Key &key,
                                                std::size_t attempt) const {
  return (this->hashFunction(key) + attempt) % hashTable.size();
}

template <class Key, class Value, template <class> class Hash>
bool OpenAddressing<Key, Value, Hash>::isEmpty() const {
  return itemCount == 0;
}

template <class Key, class Value, template <class> class Hash>
std::size_t OpenAddressing<Key, Value, Hash>::size() const {
  return itemCount;
}

template <class Key, class Value, template <class> class Hash>
std::size_t OpenAddressing<Key, Value, Hash>::capacity() const {
  return hashTable.capacity();
}

template <class Key, class Value, template <class> class Hash>
double OpenAddressing<Key, Value, Hash>::getLoadFactor(int itemDelta) const {
  return static_cast<double>(size() + itemDelta) / capacity();
}