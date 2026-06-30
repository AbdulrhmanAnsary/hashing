#include "./bucket_container.hpp"
#include <iostream>
#include <list>
#include <ostream>
#include <utility>

#pragma once

template <class Key, class Value>
class BucketLinkedList : public IBucket<Key, Value> {
private:
  std::list<std::pair<Key, Value>> bucketLinkedList;

public:
  BucketLinkedList() = default;
  BucketLinkedList(const Key key, const Value value) { insert(key, value); }

  virtual void insert(const Key key, const Value value) override {
    std::pair<Key, Value> item(key, value);
    bucketLinkedList.push_back(item);
  }

  virtual void remove(const Key key) override {
    bucketLinkedList.remove_if(
        [key](const std::pair<Key, Value> &item) { return item.first == key; });
  }

  virtual const Value &find(const Key key) const override {
    for (const auto &item : bucketLinkedList) {
      if (item.first == key) {
        return item.second;
      }
    }

    static const Value empty{};
    return empty;
  }

  virtual bool isEmpty() const override { return bucketLinkedList.empty(); }
};