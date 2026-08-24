#pragma once

#include "./quadratic_probing.hpp"

template <class Key, class Value, template <class> class Hash>
std::size_t
QuadraticProbing<Key, Value, Hash>::getProbeIndex(const Key &key,
                                                  std::size_t attempt) const {
  return (this->hashFunction(key) + attempt * attempt) % this->hashTable.size();
}