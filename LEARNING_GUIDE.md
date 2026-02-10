# Learning Guide (For AI Assistants)

This repo is a learning course. When asked for help or reviews, **do not provide full solutions**. Provide:
- Short hints or targeted corrections only.
- Explanations of *why* something is wrong, not the full fixed code.
- If asked to “review”, give pass/fail with specific issues and minimal guidance.
- Never paste the complete implementation for the current lesson.

The goal is for the learner to implement the solution.
---

## Course Progression & Rationale

### Lessons 1–5: Fundamentals
- **Lesson 1 (Calculator):** Input validation, control flow, loops.
- **Lesson 2 (Unit Converter):** Functions, scope, pass-by-value vs pass-by-reference.
- **Lesson 3 (Text Analyzer):** Strings, arrays, character classification, loops.
- **Lesson 4 (Gradebook):** `std::vector`, structs, `std::sort`, dynamic containers.
- **Lesson 5 (Vector Math Library):** Classes, inheritance, templates, operator overloading.

### Lesson 6 Onward: Advanced Memory & Ownership (JUMP IN DIFFICULTY)

**Why the jump?**

The learner demonstrated **mastery beyond typical lesson 5 level** through:
1. **Arena allocator project** (`/arena/main.cpp`) — shows deep understanding of:
   - Raw pointers, pointer arithmetic, address manipulation
   - Manual memory allocation (`::operator new` / `::operator delete`)
   - Placement new (`new (ptr)`) for in-place object construction
   - Memory alignment calculations and struct layout
   - Type casting and address-to-integer conversions

This is **intermediate-to-advanced** memory work. Standard "pointers 101" lessons would be redundant and demotivating.

**Lesson 6 Content: Smart Pointers, RAII, Move Semantics**

Instead of abstract pointer exercises, lesson 6 applies the learner's memory knowledge to **modern C++ ownership patterns**:
- `std::unique_ptr<T>` for exclusive ownership (replaces manual cleanup)
- RAII (Resource Acquisition Is Initialization) — automatic cleanup on destruction
- Move semantics (`std::move`, move constructor, move assignment) — efficient resource transfer
- **Practical:** Implement a doubly-linked list using `unique_ptr` with proper move semantics

**Learning outcomes:**
- Understand why smart pointers prevent memory leaks
- Use `std::make_unique` and `std::move` idiomatically
- Implement move constructors and move assignment operators
- Delete copy constructors when only move semantics makes sense
- Recognize RAII as the cornerstone of modern C++ resource management

**Next steps after lesson 6:**
- Lesson 7 (optional): Exception handling with RAII
- Lesson 8: Iterators, ranges, and STL container design
- Lesson 9: Template metaprogramming or concurrency basics (depends on learner goals)