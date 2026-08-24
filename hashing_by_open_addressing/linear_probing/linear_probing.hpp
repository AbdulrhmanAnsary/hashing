#pragma once

#include "../../default_hash.hpp"
#include "../../hashing_by_open_addressing/hasing_by_open_addressing.hpp"

template <class Key, class Value, template <class> class Hash = DefaultHash>
class LinearProbing : public OpenAddressing<Key, Value, Hash> {
  using Base = OpenAddressing<Key, Value, Hash>;

public:
  using Base::Base;
};

// Template definitions
#include "linear_probing_impl.hpp"