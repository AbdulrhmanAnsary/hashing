#pragma once

#include "../../hashing_by_open_addressing/double_hashing/double_hashing.hpp"
#include "../../hashing_by_open_addressing/linear_probing/linear_probing.hpp"
#include "../../hashing_by_open_addressing/quadratic_probing/quadratic_probing.hpp"
#include "../../hashing_by_separate_chaining/bucket_container/bucket_linked_list.hpp"
#include "../../hashing_by_separate_chaining/bucket_container/bucket_vector.hpp"
#include "../../hashing_by_separate_chaining/hashing_by_separate_chaining.hpp"
#include "test_utils.hpp"
#include "gtest/gtest.h"
#include <string>

/*
 * Implementations covered by the hashing contract.
 *
 * Every type listed here must satisfy:
 *
 *     OpenAddressing Contract
 *
 * The contract tests must not depend on the specific probing strategy.
 */

using HashingImplementation =
    testing::Types<SeparateChaining<std::string, std::string>,
                   SeparateChaining<std::string, std::string, BucketVector>,
                   LinearProbing<std::string, std::string>,
                   QuadraticProbing<std::string, std::string>,
                   DoubleHashing<std::string, std::string>>;

/*
 * Implementations covered by collision-specific hashing tests.
 *
 * Every type uses collisionHash so the tests can deterministically
 * exercise collision handling without depending on the probing strategy.
 */

using HashingCollisionImplementation = testing::Types<
    SeparateChaining<std::string, std::string, BucketLinkedList, collisionHash>,
    SeparateChaining<std::string, std::string, BucketVector, collisionHash>,
    LinearProbing<std::string, std::string, collisionHash>,
    QuadraticProbing<std::string, std::string, collisionHash>,
    DoubleHashing<std::string, std::string, collisionHash, collisionHash>>;