#pragma once

#include "./bucket_container.hpp"
#include <stdexcept>
#include <utility>
#include <vector>

template <class Key, class Value>
class BucketVector : public IBucket<Key, Value> {
private:
  std::vector<std::pair<Key, Value>> bucketVector;

public:
  BucketVector() = default;
  BucketVector(const Key &key, const Value &value) { insert(key, value); }

  void insert(const Key &key, const Value &value) override {
    std::pair<Key, Value> item(key, value);
    bucketVector.push_back(item);
  }

  void remove(const Key &key) override {
    for (auto it = bucketVector.begin(); it != bucketVector.end(); ++it) {
      if (it->first == key) {
        bucketVector.erase(it);
        return;
      }
    }
  }

  const Value &find(const Key &key) const override {
    for (const auto &item : bucketVector) {
      if (item.first == key) {
        return item.second;
      }
    }

    throw std::out_of_range("'" + key + "' Key not found.");
  }

  bool contains(const Key &key) const override {
    for (const auto &item : bucketVector) {
      if (item.first == key) {
        return true;
      }
    }

    return false;
  }

  bool isEmpty() const override { return bucketVector.empty(); }

  void forEach(const std::function<void(const std::pair<Key, Value> &)>
                   &function) const override {

    for (const auto &entry : bucketVector) {
      function(entry);
    }
  }
};