# MyContainer Project - Custom Iterable Container

## 📋 Description

This project implements a generic C++ container class `MyContainer<T>` that supports insertion, removal, and advanced iteration techniques. It mimics a vector-like container but allows multiple custom traversal methods via different iterators.

The container was developed as part of an academic assignment requiring template programming, iterator design, and clean modular code.

---

## 🛠️ Features

* **Generic templated container** for any comparable type (e.g., `int`, `std::string`, `char`, etc.)
* **addElement(T)**: Adds a new element
* **remove(T)**: Removes all instances of an element
* **size()**: Returns the current number of stored elements

### Supported Iterators

Each iterator provides a different way of traversing the container:

| Iterator Type             | Description                                       |
| ------------------------- | ------------------------------------------------- |
| `AscendingOrderIterator`  | Sorted from smallest to largest                   |
| `DescendingOrderIterator` | Sorted from largest to smallest                   |
| `SideCrossOrderIterator`  | Alternates from start and end towards the middle  |
| `ReverseOrderIterator`    | Reversed order of insertion                       |
| `OrderIterator`           | Regular insertion order                           |
| `MiddleOutOrderIterator`  | Starts from the middle, then outwards alternately |

Each iterator has:

* `begin_x_order()` and `end_x_order()` methods
* `operator*`, `operator++`, `operator==`, `operator!=`

---

## 📁 Files

* `MyContainer.hpp` — main header file with class and iterators
* `tests.cpp` — contains comprehensive test suite using doctest
* `main_demo_full.cpp` — full demonstration of all iterator types
* `makefile` — build system

---

## 🚀 Build & Run

### Build main demo:

```bash
make demo
./demo
```

### Run tests:

```bash
make test
```

### Check for memory leaks:

```bash
make valgrind
```

---

## ✅ Tested With

* `g++` (C++17)
* `doctest.h`
* `valgrind`
* Ubuntu 20.04/22.04, VSCode

---

## 👨‍💻 Developer Notes

* Iterators inherit from `BaseIterator` which manages an index-based traversal.
* Each iterator builds its own ordered view (`ordered_data`) and advances via index.
* Safety against `*end()` access is implemented to avoid segmentation faults.
* The code is modular, readable, and fully documented.

---

## 📚 License

This project was completed as part of an academic course and is shared for educational use.
