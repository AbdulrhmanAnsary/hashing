# TDD Imagine Usage Method

> Engineering methodology for developing software through
> imagined usage, tests, implementation, evidence, and
> engineering review.

For the current state of a specific project, see its
[dev.md](./dev.md).

        (Imagine Usage)
              ↓
       (Desired Behavior)
        What should I be
        able to write/do?
              ↓
       (Write the Test)
              ↓
            (RED)
              ↓
          (Implement)
              ↓
           (GREEN)
              ↓
          (REFACTOR)
              ↓
      (New Information)
              ↓
      (New Usage / Edge Case)
              ↓
          (New Test)
              ↓
           (repeat)

## The Model

### 0. Imagine

Before implementation, imagine how the system will actually be used.

- What will the user type?
- What does the user want to do?
- What is the natural API?
- What behavior does the user expect?
- What scenarios will the user try?
- What edge cases will the user test?
- What limits will the user want to discover?
- What failures must be predictable?
- What evidence would make the user trust the system?

Do not design the internal implementation yet.

### 1. TDD Cycle

```
RED
↓
Write the smallest meaningful test

GREEN
↓
Implement the minimum code required to pass the test

REFACTOR
↓
Preserve behavior
Improve design
Remove duplication
Clarify responsibilities
```

### 2. Expand

After a TDD cycle, use the new information to explore the next behavior.

```
New Usage
↓
Edge Case
↓
Failure Case
↓
New Requirement
↓
Test
↓
RED → GREEN → REFACTOR

Repeat until the defined behavior, important edge cases,
and failure behavior of the current feature or unit are sufficiently covered.

### 3. Engineering Review

Perform an Engineering Review when one of these triggers occurs:

- A significant decision is being made.
- An existing design or contract needs to change.
- A significant problem or unexpected behavior appears.
- A meaningful part or unit has been completed.

Review the accumulated evidence:

- Are the responsibilities correct and clear?
- Is ownership correct?
- Is the API good and still clean?
- Is there duplication?
- Has an abstraction become necessary?
- Has an existing abstraction become unnecessary?
- Are the invariants obvious and preserved?
- Does the architecture allow modification?
- Has anything become difficult or expensive to change?
- Has new information invalidated an earlier assumption?

### Review Decisions

After the review, choose explicitly:

- KEEP — The current design is still appropriate.
- REFACTOR — The design is correct, but the implementation needs improvement.
- REDESIGN — New evidence shows that the design itself needs to change.
- DEFER — The issue is known but not worth solving yet.

Update relevant design decisions or project documentation when necessary.
```
