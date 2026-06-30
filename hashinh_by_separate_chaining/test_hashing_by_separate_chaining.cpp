#include "./hashing_by_separate_chaining.hpp"
#include "gtest/gtest.h"

// normal sequence operations
TEST(HashTableTest, NewHashTableIsEmpty) {
  SeparateChaining<std::string, long int> phoneBock;

  EXPECT_TRUE(phoneBock.isEmpty());
}

TEST(HashTableTest, InsertItems) {
  SeparateChaining<std::string, long int> phoneBock;

  phoneBock.insert("Abdulrhman", 201234567891);
  phoneBock.insert("Fatma", 201533458516);
  phoneBock.insert("Saad", 201024846746);

  EXPECT_FALSE(phoneBock.isEmpty());
  EXPECT_EQ(phoneBock.size(), 3);
  EXPECT_EQ(phoneBock["Abdulrhman"], 201234567891);
}