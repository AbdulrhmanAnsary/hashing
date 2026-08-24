#pragma once

// Shared test utilities for hash table unit tests.
// Use this header in any test file that needs consistent test assertions.

#include "diagnostic_error.hpp"
#include "gtest/gtest.h"
#include <cstddef>
#include <string>

template <typename HashTableObject>
::testing::AssertionResult
checkTableSize(const HashTableObject &hashTableObject,
               std::size_t expectedSize) {
  std::size_t actualSize = hashTableObject.size();

  if (actualSize == expectedSize) {
    return ::testing::AssertionSuccess();
  }

  DiagnosticError error;
  error.setTitle("HASH TABLE SIZE VERIFICATION FAILED");
  error.setFailureReason("The expected size doesn't equals the actual size.");

  return ::testing::AssertionFailure()
         << error.getErrorMessage("size()", std::to_string(expectedSize),
                                  std::to_string(actualSize));
}

template <typename HashTableObject>
::testing::AssertionResult
checkTableSizeNotZero(const HashTableObject &hashTableObject) {
  std::size_t actualSize = hashTableObject.size();
  std::size_t expectedSize = static_cast<std::size_t>(0);

  if (actualSize <= expectedSize) {
    DiagnosticError error;
    error.setTitle("HASH TABLE SIZE NOT EQUALS ZERO VERIFICATION FAILED");
    error.setFailureReason(
        "The size of the hash table is less than or equal to zero.");

    return ::testing::AssertionFailure()
           << error.getErrorMessage("size()", std::to_string(expectedSize),
                                    std::to_string(actualSize));
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject>
::testing::AssertionResult
checkTableEmpty(const HashTableObject &hashTableObject) {
  DiagnosticError error;
  error.setContext("checkTableEmpty()");

  if (!hashTableObject.isEmpty()) {
    error.setTitle("HASH TABLE EMPTY VERIFICATION FAILED");
    error.setFailureReason("The hash table is not empty.");

    return ::testing::AssertionFailure()
           << error.getErrorMessage("isEmpty()", "True", "False");
  }

  if (auto result =
          checkTableSize(hashTableObject, static_cast<std::size_t>(0));
      !result) {
    return result;
  }

  if (auto loadFactor = hashTableObject.getLoadFactor(); loadFactor > 0) {
    error.setTitle("HASH TABLE EMPTY VERIFICATION FAILED");
    error.setFailureReason("Load factor result greater than zero.");

    return ::testing::AssertionFailure() << error.getErrorMessage(
               "loadFactor()", "loadFactor() = 0", std::to_string(loadFactor));
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject>
::testing::AssertionResult
checkTableNotEmpty(const HashTableObject &hashTableObject) {
  DiagnosticError error;
  error.setContext("checkTableNotEmpty()");

  if (hashTableObject.isEmpty()) {
    error.setTitle("HASH TABLE NOT EMPTY VERIFICATION FAILED");
    error.setFailureReason("The hash table is empty.");

    return ::testing::AssertionFailure()
           << error.getErrorMessage("isEmpty()", "False", "True");
  }

  if (auto result = checkTableSizeNotZero(hashTableObject); !result) {
    return result;
  }

  if (auto loadFactor = hashTableObject.getLoadFactor(); loadFactor <= 0) {
    error.setTitle("HASH TABLE EMPTY VERIFICATION FAILED");
    error.setFailureReason("Load factor result less than or equals zero.");

    return ::testing::AssertionFailure() << error.getErrorMessage(
               "loadFactor()", "loadFactor() > 0", std::to_string(loadFactor));
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult
checkTableContains(const HashTableObject &hashTableObject, Key key,
                   Value expectedValue) {
  DiagnosticError error;

  if (!hashTableObject.contains(key)) {
    error.setTitle("HASH TABLE FIND VERIFICATION FAILED");
    error.setFailureReason("Key '", key, "' ", "Not Found.");

    return ::testing::AssertionFailure()
           << error.getErrorMessage("contains()", "True", "False");
  }

  const auto &actualValue = hashTableObject.find(key);

  if (expectedValue != actualValue) {
    error.setTitle("HASH TABLE FIND VERIFICATION FAILED");
    error.setFailureReason("Unfound Value.");

    return ::testing::AssertionFailure() << error.getErrorMessage(
               "contains() + find()", expectedValue, actualValue);
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult
checkTableContains(const HashTableObject &hashTableObject,
                   const std::pair<Key, Value> &entry) {
  Key key = entry.first;
  Value value = entry.second;

  return checkTableContains(hashTableObject, key, value);
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult
checkTableNotContains(const HashTableObject &hashTableObject, Key key,
                      Value expectedValue) {
  DiagnosticError error;

  if (hashTableObject.contains(key)) {
    const auto &actualValue = hashTableObject.find(key);

    if (actualValue == expectedValue) {
      error.setTitle("HASH TABLE NOT CONTAINS VERIFICATION FAILED");
      error.setFailureReason("The key '", key, "' and value '", expectedValue,
                             "' were Found.");

      return ::testing::AssertionFailure() << error.getErrorMessage(
                 "contains() + find()", expectedValue, actualValue);
    }

    error.setTitle("HASH TABLE NOT CONTAINS VERIFICATION FAILED");
    error.setFailureReason("Key '", key, "' exists with a different value.");

    return ::testing::AssertionFailure() << error.getErrorMessage(
               "contains() + find()", expectedValue, actualValue);
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult
checkTableNotContains(const HashTableObject &hashTableObject,
                      const std::pair<Key, Value> &entry) {
  Key key = entry.first;
  Value value = entry.second;

  return checkTableNotContains(hashTableObject, key, value);
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult checkInsert(const HashTableObject &hashTableObject,
                                       Key key, Value value) {
  DiagnosticError error;
  error.setContext("checkInsert()");

  if (auto result = checkTableNotEmpty(hashTableObject); !result) {
    return result;
  }

  if (auto result = checkTableContains(hashTableObject, key, value); !result) {
    return result;
  }

  return ::testing::AssertionSuccess();
}

template <typename HashTableObject, typename Key, typename Value>
::testing::AssertionResult checkInsert(const HashTableObject &hashTableObject,
                                       const std::pair<Key, Value> &entry) {
  Key key = entry.first;
  Value value = entry.second;

  return checkInsert(hashTableObject, key, value);
}

template <typename Exception, typename Callable>
::testing::AssertionResult
checkThrowMessage(Callable &&operation, const std::string &expectedMessage) {
  DiagnosticError diagnostic;
  diagnostic.setContext("checkThrowMessage()");

  try {
    operation();
  } catch (const Exception &error) {
    if (error.what() == expectedMessage) {
      return ::testing::AssertionSuccess();
    }

    diagnostic.setTitle("EXCEPTION MESSAGE VERIFICATION FAILED");
    diagnostic.setFailureReason(
        "The expected exception was thrown, but the message is incorrect.");

    return ::testing::AssertionFailure() << diagnostic.getErrorMessage(
               "exception.what()", expectedMessage, error.what());
  } catch (...) {
    diagnostic.setTitle("EXCEPTION TYPE VERIFICATION FAILED");
    diagnostic.setFailureReason("An unexpected exception type was thrown.");

    return ::testing::AssertionFailure()
           << diagnostic.getErrorMessage("exception", "expected exception type",
                                         "unexpected exception type");
  }

  diagnostic.setTitle("EXCEPTION VERIFICATION FAILED");
  diagnostic.setFailureReason(
      "The operation did not throw the expected exception.");

  return ::testing::AssertionFailure() << diagnostic.getErrorMessage(
             "exception", "expected exception", "no exception");
}

// ========================= Integrated Testing Tools =========================

constexpr const char *KEY_PREFIX = "key_";
constexpr const char *VALUE_PREFIX = "value_";

template <typename HashTableObject>
void insertItems(HashTableObject &hashTableObject, std::size_t numOfItems) {
  for (std::size_t i = 1; i <= numOfItems; ++i) {
    hashTableObject.insert(KEY_PREFIX + std::to_string(i),
                           VALUE_PREFIX + std::to_string(i));
  }
}

template <typename HashTableObject>
void removeItems(HashTableObject &hashTableObject, std::size_t numOfItems) {
  for (std::size_t i = 1; i <= numOfItems; ++i) {
    hashTableObject.remove(KEY_PREFIX + std::to_string(i));
  }
}

template <typename HashTableObject>
void removeItems(HashTableObject &hashTableObject, std::size_t fromKey,
                 std::size_t toKey) {
  for (std::size_t i = fromKey; i <= toKey; ++i) {
    hashTableObject.remove(KEY_PREFIX + std::to_string(i));
  }
}

template <typename HashTableObject>
void printItems(const HashTableObject &hashTableObject,
                std::size_t numOfItems = 10) {

  std::cout << "\033[1;33m"
            << "NOTE:\n"
            << "  printItems() prints only the test data generated by\n"
            << "  insertItems().\n\n"
            << "  Expected key format:\n"
            << "    key_1, key_2, ..., key_n\n\n"
            << "  Expected value format:\n"
            << "    value_1, value_2, ..., value_n\n\n"
            << "  Any item that does not follow this convention\n"
            << "  (e.g. \"Jacob\" -> \"010154\") will NOT be displayed."
            << "\033[0m\n\n";

  std::cout << "================ HASH TABLE ITEMS ================\n";

  numOfItems = hashTableObject.size();

  for (std::size_t i = 1; i <= numOfItems; ++i) {
    std::string key = KEY_PREFIX + std::to_string(i);

    if (hashTableObject.contains(key)) {
      std::cout << key << " -> " << hashTableObject.find(key) << '\n';
    } else {
      std::cout << "\033[31m" << key << " -> <NOT FOUND>"
                << "\033[0m\n";
    }
  }

  std::cout << "--------------------------------\n";
  std::cout << "Size        : " << hashTableObject.size() << '\n';
  std::cout << "Capacity    : " << hashTableObject.capacity() << '\n';
  std::cout << "Load Factor : " << hashTableObject.getLoadFactor() << '\n';
  std::cout << "==================================================\n";
}

template <class Key> struct collisionHash {
  // Primary hash
  std::size_t operator()(const Key &) const {
    // std::cout << "\033[1;36m" << "The collisionHash(key) function was used"
    //           << "\033[0m\n";

    return 0;
  }

  // Capacity-aware hash
  std::size_t operator()(const Key &, std::size_t) const {
    // std::cout << "\033[1;36m"
    //           << "The collisionHash(key, capacity) function was used"
    //           << "\033[0m\n";

    return 1;
  }

  // Secondary hash for Double Hashing
  std::size_t operator()(const Key &, std::size_t, std::size_t) const {
    // std::cout << "\033[1;36m"
    //           << "The collisionHash(key, capacity) function was used"
    //           << "\033[0m\n";

    return 1;
  }
};

// ============================== Test Macros ==============================

// Wrapper macro for declaring a test case.
// This provides a single shared name for all tests in the project.
#define TEST_TEST(test_suite_name, test_name) TEST(test_suite_name, test_name)

#define EXPECT_TABLE_EMPTY(hash_table_object)                                  \
  do {                                                                         \
    EXPECT_TRUE(checkTableEmpty(hash_table_object));                           \
  } while (0)

#define EXPECT_TABLE_NOT_EMPTY(hash_table_object)                              \
  do {                                                                         \
    EXPECT_TRUE(checkTableNotEmpty(hash_table_object));                        \
  } while (0)

#define EXPECT_TABLE_SIZE(hash_table_object, expected_size)                    \
  do {                                                                         \
    EXPECT_TRUE(checkTableSize(hash_table_object,                              \
                               static_cast<std::size_t>(expected_size)));      \
  } while (0)

#define EXPECT_TABLE_CONTAINS(hash_table_object, ...)                          \
  do {                                                                         \
    EXPECT_TRUE(checkTableContains(hash_table_object, __VA_ARGS__));           \
  } while (0)

#define EXPECT_TABLE_NOT_CONTAINS(hash_table_object, ...)                      \
  do {                                                                         \
    EXPECT_TRUE(checkTableNotContains(hash_table_object, __VA_ARGS__));        \
  } while (0)

#define EXPECT_INSERTED(hash_table_object, ...)                                \
  do {                                                                         \
    EXPECT_TRUE(checkInsert(hash_table_object, __VA_ARGS__));                  \
  } while (0)

#define EXPECT_THROW_MESSAGE(operation, exception_type, expected_message)      \
  do {                                                                         \
    EXPECT_TRUE(checkThrowMessage<exception_type>([&]() { operation; },        \
                                                  expected_message))           \
        << "\n\033[0;31m" << "Throwing Operation: " #operation << "\033[0m";   \
  } while (0)