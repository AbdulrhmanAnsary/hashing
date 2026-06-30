# 🧭 Hashing

> Project description

Apply hashing and collision handling using separate chaining and open addressing

## 🎯 Vision

> Why does this project exist?

- Problem: how to retrieve element using the index in o(1) time
- Target user: data structures students
- Core value: learn hashing and collision handling
- Definition of Final Success: make a hash table that can handle any count and type of items with a load factor equals 0.75 and the ability to handle collisions using separate chaining or open addressing as the user decide and a hash function that can reduce the collisions as it possible using the mathematical equations

---

## 🧱 MVP (Minimum Viable Product)

### Hash Functions:

- insert()
- remove()
- find()
- isEmpty()
- size()
- capacity()
- loadFactor()

### collision handling:

**separate chaining:**

- linked list

**open addressing:**

- liner probing
- quadratic probing
- double hashing

---

## 👤 User Flow

1. User import hashing in his project
2. user defined object from hashing with any type with the ability to specify the hash table size
3. user used one or more from hashing function like insert or remove
4. hashing can retrieval items in o(1) and handle collisions

---

## 🧠 Architecture (High-Level Design)

### Diagram

C:\Users\Abdulrhman\OneDrive\المستندات\hashing.drawio

### Key Decisions

- Why this design? because every thing is independent and the user has the freedom to customize "hashing" from any point he want
- Trade-offs:

---

## 🏃 Sprint Backlog ['Week']

- write the project interfaces and classes
- write the implementation for the project interfaces and classes

---

## 🔄 Sprint Progress

---

## 📍 Current Focus (To Do)

> If there are more than two tasks here, you are probably multitasking too much.

- [ ] write tests that has the ability to test the normal, edge and error cases for the entire project (TDD benefits)

### Definition of Done

when that exists a tests for linear_probing, quadratic_probing, double_hashing and hashinh_by_separate_chaining

---

## 📊 Done

...

---

## 🧩 Out of Scope

> Future ideas and features.

- 'Feature Idea 1'
- 'Feature Idea 2'
- 'Performance Improvements'

---

## 🧪 Review / Test

...

---

## 🧠 Decisions Log

- 'Decision and reason'

---
