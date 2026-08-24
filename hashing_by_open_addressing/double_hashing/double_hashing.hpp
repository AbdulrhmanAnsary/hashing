#pragma once

#include "../../default_hash.hpp"
#include "../../hashing_by_open_addressing/hasing_by_open_addressing.hpp"
#include "../../math_utilities/math_cache.hpp"
#include "./default_secondary_hash.hpp"
#include <cstddef>

template <class Key, class Value, template <class> class Hash = DefaultHash,
          template <class> class SecondaryHash = DefaultSecondaryHash>
class DoubleHashing : public OpenAddressing<Key, Value, Hash> {

  using Base = OpenAddressing<Key, Value, Hash>;

protected:
  SecondaryHash<Key> secondaryHash;
  mutable MathCache<std::size_t, std::size_t> secondaryProbingCache;

public:
  using Base::Base;

  std::size_t getProbeIndex(const Key &key, std::size_t attempt) const override;
};

#include "./double_hashing_impl.hpp"