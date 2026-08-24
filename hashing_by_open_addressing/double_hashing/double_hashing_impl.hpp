#pragma once

#include "../../math_utilities/prime_utils.hpp"
#include "./double_hashing.hpp"

template <class Key, class Value, template <class> class Hash,
          template <class> class SecondaryHash>
std::size_t DoubleHashing<Key, Value, Hash, SecondaryHash>::getProbeIndex(
    const Key &key, std::size_t attempt) const {
  const std::size_t h1 = this->hashFunction(key);

  // Choose a prime smaller than but close from the table capacity.
  const std::size_t capacity = this->capacity();
  const std::size_t prime = PrimeUtils::getPrimeNumber(
      capacity, this->secondaryProbingCache, [capacity](std::size_t) {
        return PrimeUtils::getLastPrimeNumber(capacity / 2, capacity - 1);
      });
  const std::size_t h2 = secondaryHash(key, capacity, prime);

  return (h1 + attempt * h2) % this->hashTable.size();
}