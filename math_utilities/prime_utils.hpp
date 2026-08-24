#pragma once

#include "./math_cache.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>

class PrimeUtils {
public:
  static bool isPrime(std::size_t number) {
    if (number == 2) {
      return true;
    }

    if (number < 2 || number % 2 == 0) {
      return false;
    }

    for (std::size_t divisor = 3; divisor <= number / divisor; divisor += 2) {
      if (number % divisor == 0) {
        return false;
      }
    }

    return true;
  }

  template <class PrimeSearch>
  static std::size_t getPrimeNumber(const std::size_t &key,
                                    MathCache<std::size_t, std::size_t> &cache,
                                    PrimeSearch &&primeSearch) {

    if (cache.contains(key)) {
      return cache.get(key);
    }

    const std::size_t prime = std::forward<PrimeSearch>(primeSearch)(key);
    cache.put(key, prime);

    return prime;
  }

  static std::size_t getNextPrimeNumber(std::size_t minNumber) {
    if (minNumber <= 2) {
      return 2;
    }

    if (minNumber % 2 == 0) {
      ++minNumber;
    }

    while (!isPrime(minNumber)) {
      minNumber += 2;
    }

    return minNumber;
  }

  static std::size_t getFirstPrimeNumber(std::size_t from, std::size_t to) {
    if (from > to) {
      throw std::invalid_argument("Invalid range: from must be <= to [" +
                                  std::to_string(from) + ", " +
                                  std::to_string(to) + "].");
    }

    if (from <= 2 && 2 <= to) {
      return 2;
    }

    if (from % 2 == 0) {
      ++from;
    }

    for (std::size_t number = from; number <= to;) {
      if (isPrime(number)) {
        return number;
      }

      if (number > to - 2) {
        break;
      }

      number += 2;
    }

    throw std::invalid_argument("No prime number exists in the given range [" +
                                std::to_string(from) + ", " +
                                std::to_string(to) + "].");
  }

  static std::size_t getLastPrimeNumber(std::size_t from, std::size_t to) {
    if (from > to) {
      throw std::invalid_argument("Invalid range: from must be <= to [" +
                                  std::to_string(from) + ", " +
                                  std::to_string(to) + "].");
    }

    if (to >= 2) {

      if (to % 2 == 0) {
        --to;
      }

      for (std::size_t number = to; number >= from;) {
        if (isPrime(number)) {
          return number;
        }

        if (number <= from + 1 || number < 2) {
          break;
        }

        number -= 2;
      }

      if (from <= 2) {
        return 2;
      }
    }

    throw std::invalid_argument("No prime number exists in the given range [" +
                                std::to_string(from) + ", " +
                                std::to_string(to) + "].");
  }
};