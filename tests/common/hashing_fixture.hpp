#pragma once

#include "gtest/gtest.h"

/*
 * Fixture shared by all hashing contract tests.
 *
 * The fixture intentionally knows nothing about the probing strategy.
 * It only provides an object satisfying the hashing interface.
 */

template <typename HashingObject> class HashingTest : public testing::Test {
protected:
  HashingObject hashing;
};

template <typename HashingObject>
class HashingCollisionTest : public testing::Test {
protected:
  HashingObject hashing;
};