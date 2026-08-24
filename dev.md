# Engineering Method

This project follows the
[TDD Imagine Usage Method](./TDD-Imagine-Usage-Method.md).

This document defines the engineering methodology used to
design, test, implement, evaluate, and evolve the project.

For the current state and execution of this project, see this
dashboard.

---

# Project Dashboard

| Property           | Value           |
| ------------------ | --------------- |
| Project            | Hashing         |
| Status             | In Progress     |
| Estimated Effort   | 34h             |
| Daily Allocation   | 2h/day          |
| Estimated Duration | 17 working days |
| Actual Effort      | ...             |
| Estimate Variance  | ...             |
| Started            | 20-May-2026     |
| Completed          | ...             |

---

# 📌 Project

## Name

Hashing

## Version

v0.1.0

## Problem

Efficiently retrieve values by key in expected **O(1)** time while handling collisions correctly.

## Target Users

- Data Structures students.
- C++ learners.
- Developers interested in hash table internals.

## Core Value

Learn and implement hashing from scratch while building a reusable and extensible library.

## Definition of Done

- [ ] All features implemented.
- [ ] Tests added.
- [ ] All tests passing.
- [ ] Documentation updated.
- [ ] No compiler warnings.
- [ ] Code formatted.
- [ ] Requirements satisfied.
- [ ] Ready to merge.

---

# ⚙ Requirements

## Functional Requirements

- Store key-value pairs.
- Generic key and value types.
- Insert, remove, and search operations.
- Automatic resizing.
- Configurable collision strategy.

## Non-Functional Requirements

- Expected O(1) average complexity.
- Memory safe.
- Easy to extend.
- Modern C++ style.
- High test coverage.

## Constraints

- C++ templates only.
- No memory leaks.
- Collision strategy must be replaceable.
- Load factor threshold = 0.75.

---

# 👤 User Flow

1. Include the hashing library.
2. Create a hash table with the desired key and value types.
3. Select the collision handling strategy.
4. Insert, search, and remove elements.

---

# 🏗 Architecture

## High-Level Design

The hash table delegates collision handling to interchangeable strategies, allowing the implementation to remain modular and extensible.

## Main Components

- Hash Table
- Hash Function
- Collision Strategy
- Rehash Manager
- insert, remove, lookup and hash table state function

## Project Structure

```
hashing_by_open_addressing/
hashing_by_separate_chaining/
tests/
```

---

# 🚀 MVP (Minimum Viable Product)

## Core Features

- insert()
- remove()
- find()
- contains()
- isEmpty()
- size()
- capacity()
- getLoadFactor() maintained at 0.75
- Generic template implementation.
- Automatic rehashing.

## Collision Handling

### Separate Chaining

- [ ] Linked List

### Open Addressing

- [ ] Linear Probing
- [ ] Quadratic Probing
- [ ] Double Hashing

---

# Workflow

## 📥 Backlog

- [ ] Open Addressing Collision Handling:
  1. Linear Hashing
  2. Quadratic Probing
  3. Double Hashing

- [ ] Integrity:
  1. EXPECT_LOAD_FACTOR
  2. EXPECT_CAPACITY
  3. EXPECT_REHASH
  4. EXPECT_BUCKET_COUNT

## 📅 Sprint Backlog [Week]

### Goal

Build a complete TDD test suite before implementing production code.

### Tasks

- finish test hashing contract:

## 🚧 In Progress

- [ ] Contract Test:
  1. Rehashing
  2. Duplicate Key Handling
  3. Exceptions
  4. Stress Test

- [ ] Rehash() and reserve()
- [ ] getNextPrimeCapacity
- [ ] remove() probing

## 🐞 Bugs

- [ ]

## 👀 Review And Testing

- [ ]

## ✅ Done

- [x] Project structure
- [x] Initial architecture
- [x] Separate Chaining: loadFactor()

- [x] Table State:
  1. check table state
  2. EXPECT_TABLE_EMPTY
  3. EXPECT_TABLE_NOT_EMPTY
  4. EXPECT_TABLE_SIZE

- [x] Lookup:
  1. EXPECT_TABLE_CONTAINS
  2. EXPECT_TABLE_NOT_CONTAINS

- [ ] Contract Test:

---

# 📚 References

- cppreference
- Introduction to Algorithms (CLRS)
- OpenDSA Hash Tables

---

# 💡 Ideas

- Visualize collision distribution.
- Support custom allocators.
- Custom hash functions.
- Iterator support.

---

# 🧠 Decisions Log

## YYYY-MM-DD

### Decision

>

### Reason

>

### Alternatives

>
