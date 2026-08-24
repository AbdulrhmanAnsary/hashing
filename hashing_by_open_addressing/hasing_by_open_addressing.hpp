#pragma once

#include "../default_hash.hpp"
#include "../hashing.hpp"
#include "../math_utilities/math_cache.hpp"
#include <cstddef>
#include <vector>

/*
 * Open addressing hash table using linear probing by default.
 *
 * This class provides the complete open addressing implementation,
 * including insertion, lookup, deletion, rehashing, resizing, and
 * load-factor management.
 *
 * Derived classes can specialize this implementation by overriding
 * only the behavior that differs from the default strategy.
 */

template <class Key, class Value, template <class> class Hash = DefaultHash>
class OpenAddressing : public IHashing<Key, Value, Hash> {
protected:
  enum class SlotState { Empty, Occupied, Delete };

  struct Entry {
    Key key;
    Value value;
    SlotState state = SlotState::Empty;

    Entry() {}

    Entry(const Key &key, const Value &value, SlotState state)
        : key(key), value(value), state(state) {}

    bool isOccupied() const { return state == SlotState::Occupied; }

    bool isEmpty() const { return state == SlotState::Empty; }

    bool isDeleted() const { return state == SlotState::Delete; }

    bool isNotOccupied() const { return isEmpty() || isDeleted(); }
  };

protected:
  std::vector<Entry> hashTable;
  std::size_t itemCount = 0;
  mutable MathCache<std::size_t, std::size_t> probingCache;
  static constexpr double MAX_LOAD_FACTOR = 0.75;
  static constexpr double MIN_LOAD_FACTOR = 0.30;
  static constexpr std::size_t MIN_CAPACITY = 5;

public:
  OpenAddressing(std::size_t initialCapacity = 10);
  OpenAddressing(const Key &key, const Value &value,
                 std::size_t initialCapacity = 10);

  virtual void insert(const Key &key, const Value &value) override;
  virtual void insert(const std::pair<Key, Value> &entry) override;
  virtual void remove(const Key &key) override;
  virtual void rehash(std::size_t newCapacity) override;
  virtual void reserve(std::size_t expectedItems) override;
  virtual const Value &find(const Key &key) const override;
  virtual bool contains(const Key &key) const override;

  virtual std::size_t getProbeIndex(const Key &key, std::size_t attempt) const;

  virtual bool isEmpty() const override;
  virtual std::size_t size() const override;
  virtual std::size_t capacity() const override;
  virtual double getLoadFactor(int itemDelta = 0) const override;
};

// Template definitions
#include "./hasing_by_open_addressing_impl.hpp"