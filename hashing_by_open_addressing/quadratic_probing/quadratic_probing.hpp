#pragma once

#include "../../default_hash.hpp"
#include "../../hashing_by_open_addressing/hasing_by_open_addressing.hpp"

template <class Key, class Value, template <class> class Hash = DefaultHash>
class QuadraticProbing : public OpenAddressing<Key, Value, Hash> {
  using Base = OpenAddressing<Key, Value, Hash>;

public:
  using Base::Base;

  std::size_t getProbeIndex(const Key &key, std::size_t attempt) const override;
};

// Template definitions
#include "quadratic_probing_impl.hpp"