#pragma once

#include "./test_types.hpp"

// Improve google TYPED_TEST outputs by specify the types names

struct HashNames {
  template <typename T> static std::string GetName(int);
};

// ==================== Separate Chaining ====================

template <>
inline std::string
HashNames::GetName<SeparateChaining<std::string, std::string>>(int) {
  return "SeparateChaining<BucketLinkedList>";
}

template <>
inline std::string
HashNames::GetName<SeparateChaining<std::string, std::string, BucketVector>>(
    int) {
  return "SeparateChaining<BucketVector>";
}

// Separate Chaining collisionHash

template <>
inline std::string
HashNames::GetName<SeparateChaining<std::string, std::string, BucketLinkedList,
                                    collisionHash>>(int) {
  return "SeparateChaining<BucketLinkedList>";
}

template <>
inline std::string HashNames::GetName<
    SeparateChaining<std::string, std::string, BucketVector, collisionHash>>(
    int) {
  return "SeparateChaining<BucketVector>";
}

// ==================== Open Addressing ====================

template <>
inline std::string
HashNames::GetName<LinearProbing<std::string, std::string>>(int) {
  return "LinearProbing";
}

template <>
inline std::string
HashNames::GetName<QuadraticProbing<std::string, std::string>>(int) {
  return "QuadraticProbing";
}

template <>
inline std::string
HashNames::GetName<DoubleHashing<std::string, std::string>>(int) {
  return "DoubleHashing";
}

// Open Addressing collisionHash

template <>
inline std::string
HashNames::GetName<LinearProbing<std::string, std::string, collisionHash>>(
    int) {
  return "LinearProbingCollision";
}

template <>
inline std::string
HashNames::GetName<QuadraticProbing<std::string, std::string, collisionHash>>(
    int) {
  return "QuadraticProbingCollision";
}

template <>
inline std::string HashNames::GetName<
    DoubleHashing<std::string, std::string, collisionHash, collisionHash>>(
    int) {
  return "DoubleHashingCollision";
}