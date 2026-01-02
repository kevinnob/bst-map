# BST Map — Binary Search Tree–Backed Associative Container (C++)

A C++17 implementation of a **map (associative container)** built on top of a custom
**Binary Search Tree (BST)**.  
This project demonstrates **recursive data structures**, **templates**, **functors**, and
**iterator reuse** to construct a container with `std::map`-like behavior.

---

## Overview

The project implements two tightly coupled abstractions:

1. **`BinarySearchTree<T, Compare>`** — a generic, recursive BST with strict ordering invariants  
2. **`Map<K, V, Compare>`** — an associative container implemented *using* the BST (has-a pattern)

The `Map` stores key–value pairs while enforcing ordering **only on keys**, allowing values to be modified safely without breaking the tree structure.

---

## Key Features

- Recursive **binary search tree** implementation with:
  - No-duplicates invariant
  - Strict sorting invariant
  - Custom comparator support via functors
- **Map ADT** with `std::map`-like interface:
  - `insert`
  - `find`
  - `operator[]`
  - Iteration over key–value pairs
- Reuse of **BST iterators** to power map iteration
- Extensive **unit testing**, including tests designed to catch buggy implementations

---

## Technical Highlights

- Recursive implementations of all BST operations (no iteration)
- Template-based design supporting arbitrary key and value types
- Custom comparator functor for comparing key–value pairs
- Clear separation between **data structure** (BST) and **container abstraction** (Map)
- Iterator semantics consistent with standard library containers
- Defensive handling of edge cases (empty trees, missing keys, invariant checks)

---

## Project Structure

```
.
├── BinarySearchTree.hpp        # Recursive BST implementation
├── BinarySearchTree_tests.cpp  # Unit tests for BST
├── Map.hpp                     # Map ADT built on BST
├── Map_tests.cpp               # Map unit tests
├── TreePrint.hpp               # Debugging / visualization helper
├── Makefile
```

---

## Build & Test

### Build everything
```bash
make -j4
```

### Run all tests
```bash
make test
```

### Run individual test suites
```bash
make BinarySearchTree_tests.exe && ./BinarySearchTree_tests.exe
make Map_tests.exe && ./Map_tests.exe
```

---

## Example Usage

```cpp
Map<std::string, int> counts;

counts["apple"] = 3;
counts.insert({"banana", 5});

auto it = counts.find("apple");
if (it != counts.end()) {
    std::cout << it->first << ": " << it->second << std::endl;
}

for (const auto &kv : counts) {
    std::cout << kv.first << " -> " << kv.second << std::endl;
}
```

---

## Why This Project Matters

This project emphasizes **fundamental CS concepts** that underlie many real systems:

- Recursive reasoning over tree-structured data
- Maintaining representation invariants
- Abstraction layering (BST → Map)
- Generic programming with templates and functors
- Iterator design and reuse
- Testing against intentionally buggy implementations

These skills directly transfer to **systems programming**, **performance-critical code**, and
**core library development**.

---

## Notes

- The BST implementation does not self-balance; correctness and invariants are prioritized over rebalancing.
- Map iteration order reflects the sorted order of keys.
- The design intentionally mirrors standard library container behavior.

---

## License

Student-authored code.  
Reuse with attribution.
