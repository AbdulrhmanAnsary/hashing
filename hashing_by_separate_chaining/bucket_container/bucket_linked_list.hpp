#pragma once

#include "./bucket_container.hpp"
#include <list>
#include <stdexcept>
#include <utility>

template <class Key, class Value>
class BucketLinkedList : public IBucket<Key, Value> {
private:
  std::list<std::pair<Key, Value>> bucketLinkedList;

public:
  BucketLinkedList() = default;
  BucketLinkedList(const Key &key, const Value &value) { insert(key, value); }

  virtual void insert(const Key &key, const Value &value) override {
    std::pair<Key, Value> item(key, value);
    bucketLinkedList.push_back(item);
  }

  virtual void remove(const Key &key) override {
    bucketLinkedList.remove_if(
        [key](const std::pair<Key, Value> &item) { return item.first == key; });
  }

  virtual const Value &find(const Key &key) const override {
    for (const auto &item : bucketLinkedList) {
      if (item.first == key) {
        return item.second;
      }
    }

    throw std::out_of_range("'" + key + "' Key not found.");
  }

  virtual bool contains(const Key &key) const override {
    for (const auto &item : bucketLinkedList) {
      if (item.first == key) {
        return true;
      }
    }

    return false;
  }

  virtual bool isEmpty() const override { return bucketLinkedList.empty(); }

  virtual void forEach(const std::function<void(const std::pair<Key, Value> &)>
                           &function) const override {

    for (const auto &entry : bucketLinkedList) {
      function(entry);
    }
  }
};