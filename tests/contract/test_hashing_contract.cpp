#include "../common/hashing_fixture.hpp"
#include "../common/hashing_names.hpp"
#include "../common/test_types.hpp"
#include "../common/test_utils.hpp"
#include "gtest/gtest.h"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<std::string, std::string>> phoneBook = {
    {"Abdulrhman", "201234567891"}, {"Fatma", "201533458516"},
    {"Saad", "201024846742"},       {"Ali", "201547862458"},
    {"Omer", "201198746352"},       {"Gamale", "201057932474"},
    {"Syed", "201236975269"},       {"Tamer", "201164287541"},
    {"Michael", "201586423478"},    {"Jacob", "201225486241"}};

// ==================== Helper Test Functions ====================

template <typename HashingObject>
void testNewHashTableIsEmpty(HashingObject &hashing) {
  EXPECT_TABLE_EMPTY(hashing);
}

template <typename HashingObject> void testInsertItems(HashingObject &hashing) {
  hashing.insert(phoneBook[0]);
  EXPECT_INSERTED(hashing, phoneBook[0]);

  hashing.insert(phoneBook[1]);
  EXPECT_INSERTED(hashing, phoneBook[1]);

  hashing.insert(phoneBook[2]);
  EXPECT_INSERTED(hashing, phoneBook[2]);

  EXPECT_TABLE_SIZE(hashing, 3);

  EXPECT_TABLE_NOT_CONTAINS(hashing, "Michael", "201234567891");
  EXPECT_TABLE_NOT_CONTAINS(hashing, "Salah", "201234567891");
}

template <typename HashingObject>
void testRejectsDuplicateKeyWithoutCorruptingTable(HashingObject &hashing) {
  hashing.insert(phoneBook[0]);
  hashing.insert(phoneBook[1]);
  hashing.insert(phoneBook[2]);

  EXPECT_THROW_MESSAGE(hashing.insert(phoneBook[0]), std::invalid_argument,
                       "'" + phoneBook[0].first + "' Key already exists.");

  EXPECT_TABLE_SIZE(hashing, 3);

  EXPECT_TABLE_CONTAINS(hashing, phoneBook[0]);
  EXPECT_TABLE_CONTAINS(hashing, phoneBook[1]);
  EXPECT_TABLE_CONTAINS(hashing, phoneBook[2]);
}

template <typename HashingObject> void testRemoveItems(HashingObject &hashing) {
  hashing.insert(phoneBook[0]);
  hashing.insert(phoneBook[1]);
  hashing.insert(phoneBook[2]);
  hashing.insert(phoneBook[3]);
  hashing.insert(phoneBook[4]);

  EXPECT_TABLE_SIZE(hashing, 5);

  hashing.remove(phoneBook[3].first);
  hashing.remove(phoneBook[1].first);

  EXPECT_TABLE_NOT_CONTAINS(hashing, phoneBook[3]);
  EXPECT_TABLE_NOT_CONTAINS(hashing, phoneBook[1]);

  EXPECT_TABLE_SIZE(hashing, 3);
}

template <typename HashingObject>
void testExpectThrowMessage(HashingObject &hashing) {
  hashing.insert(phoneBook[0]);
  hashing.insert(phoneBook[1]);
  hashing.insert(phoneBook[2]);
  hashing.insert(phoneBook[3]);
  hashing.insert(phoneBook[4]);

  // Duplicate key
  EXPECT_THROW_MESSAGE(hashing.insert(phoneBook[0]), std::invalid_argument,
                       "'" + phoneBook[0].first + "' Key already exists.");

  // Find missing key
  EXPECT_THROW_MESSAGE(hashing.find("Unknown"), std::out_of_range,
                       "'Unknown' Key not found.");

  // Remove missing key
  EXPECT_THROW_MESSAGE(hashing.remove("Unknown"), std::out_of_range,
                       "'Unknown' Key not found.");
}

template <typename HashingObject>
void testInsertManyItems(HashingObject &hashing, std::size_t itemsCount) {
  insertItems(hashing, itemsCount);

  EXPECT_TABLE_SIZE(hashing, itemsCount);

  EXPECT_TABLE_CONTAINS(hashing, "key_1", "value_1");
  EXPECT_TABLE_CONTAINS(hashing, ("key_" + std::to_string(itemsCount / 2)),
                        ("value_" + std::to_string(itemsCount / 2)));
  EXPECT_TABLE_CONTAINS(hashing, ("key_" + std::to_string(itemsCount)),
                        ("value_" + std::to_string(itemsCount)));
}

template <typename HashingObject>
void testGrowsWhenLoadFactorLimitIsReached(HashingObject &hashing) {
  const auto initialCapacity = hashing.capacity();

  insertItems(hashing, initialCapacity);

  EXPECT_GT(hashing.capacity(), initialCapacity);
}

template <typename HashingObject>
void testShrinksWhenLoadFactorBecomesTooLow(HashingObject &hashing) {
  insertItems(hashing, 100);

  const auto capacityAfterGrowth = hashing.capacity();

  removeItems(hashing, 100);

  EXPECT_TABLE_EMPTY(hashing);

  EXPECT_LE(hashing.capacity(), capacityAfterGrowth);
}

template <typename HashingObject>
void testSurvivesGrowShrinkGrowCycle(HashingObject &hashing,
                                     std::size_t itemsCount) {
  insertItems(hashing, itemsCount);

  EXPECT_TABLE_SIZE(hashing, itemsCount);

  removeItems(hashing, itemsCount);

  EXPECT_TABLE_EMPTY(hashing);

  insertItems(hashing, itemsCount);

  EXPECT_TABLE_SIZE(hashing, itemsCount);

  EXPECT_TABLE_CONTAINS(hashing, "key_1", "value_1");
  EXPECT_TABLE_CONTAINS(hashing, ("key_" + std::to_string(itemsCount / 2)),
                        ("value_" + std::to_string(itemsCount / 2)));
  EXPECT_TABLE_CONTAINS(hashing, ("key_" + std::to_string(itemsCount)),
                        ("value_" + std::to_string(itemsCount)));
}

// ==================== Normal Tests ====================

TYPED_TEST_SUITE(HashingTest, HashingImplementation, HashNames);

TYPED_TEST(HashingTest, NewHashTableIsEmpty) {
  testNewHashTableIsEmpty(this->hashing);
}

TYPED_TEST(HashingTest, InsertItems) { testInsertItems(this->hashing); }

TYPED_TEST(HashingTest, RejectsDuplicateKeyWithoutCorruptingTable) {
  testRejectsDuplicateKeyWithoutCorruptingTable(this->hashing);
}

TYPED_TEST(HashingTest, RemoveItems) { testRemoveItems(this->hashing); }

TYPED_TEST(HashingTest, ExpectThrowMessage) {
  testExpectThrowMessage(this->hashing);
}

TYPED_TEST(HashingTest, InsertManyItems) {
  testInsertManyItems(this->hashing, 1000000);
}

TYPED_TEST(HashingTest, GrowsWhenLoadFactorLimitIsReached) {
  testGrowsWhenLoadFactorLimitIsReached(this->hashing);
}

TYPED_TEST(HashingTest, ShrinksWhenLoadFactorBecomesTooLow) {
  testShrinksWhenLoadFactorBecomesTooLow(this->hashing);
}

TYPED_TEST(HashingTest, SurvivesGrowShrinkGrowCycle) {
  testSurvivesGrowShrinkGrowCycle(this->hashing, 100000);
}

// ==================== Collision Test ====================

TYPED_TEST_SUITE(HashingCollisionTest, HashingCollisionImplementation,
                 HashNames);

TYPED_TEST(HashingCollisionTest, InsertItems) {
  testInsertItems(this->hashing);
}

TYPED_TEST(HashingCollisionTest, RejectsDuplicateKeyWithoutCorruptingTable) {
  testRejectsDuplicateKeyWithoutCorruptingTable(this->hashing);
}

TYPED_TEST(HashingCollisionTest, RemoveItems) {
  testRemoveItems(this->hashing);
}

TYPED_TEST(HashingCollisionTest, InsertManyItems) {
  testInsertManyItems(this->hashing, 10000);
}

TYPED_TEST(HashingCollisionTest, GrowsWhenLoadFactorLimitIsReached) {
  testGrowsWhenLoadFactorLimitIsReached(this->hashing);
}

TYPED_TEST(HashingCollisionTest, ShrinksWhenLoadFactorBecomesTooLow) {
  testShrinksWhenLoadFactorBecomesTooLow(this->hashing);
}

TYPED_TEST(HashingCollisionTest, SurvivesGrowShrinkGrowCycle) {
  testSurvivesGrowShrinkGrowCycle(this->hashing, 10000);
}