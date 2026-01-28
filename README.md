# 🔄 Generic Container & Custom Iterators (C++)

A robust **C++ Template Library** implementing a generic container with a suite of custom iterators. This project demonstrates advanced C++ concepts including **Generic Programming (Templates)**, **Operator Overloading**, and complex traversal algorithms.

## 🚀 Features

### 📦 Generic Container
The core `MyContainer` class is template-based, allowing it to store any data type (integers, strings, custom objects) while maintaining efficiency and type safety.

### 🔁 Custom Iterators
The library implements standard iterator traits (`begin`, `end`, `++`, `*`, `!=`) with unique traversal logic:

* **📈 Ascending Iterator:**
    Traverses the container elements in a strictly sorted order (Smallest $\to$ Largest).
    
* **🔀 Cross (Middle-Out) Iterator:**
    Implements a complex "Zig-Zag" traversal starting from the middle element and alternating outwards (e.g., Middle $\to$ Left $\to$ Right...).
    * *Example:* `[1, 2, 3, 4, 5]` $\to$ Output: `3, 2, 4, 1, 5`.

* **prime Primes Iterator:**
    A filtering iterator that automatically skips non-prime numbers, exposing only prime integers within the container.

## 🛠️ Technical Highlights
* **Template Metaprogramming:** Full usage of `template <typename T>` to ensure code reusability.
* **Smart Pointers / Memory Management:** Efficient handling of resources.
* **Operator Overloading:** Custom implementation of comparison and increment operators for seamless STL integration.
* **Unit Testing:** Rigorous testing using the **doctest** framework.

## 📂 Project Structure
```text
├── MyContainer.hpp      # Template class & Iterator implementations
├── main.cpp             # Entry point
├── Demo.cpp             # Demonstration of iterator usage
├── tests.cpp            # Unit tests covering all iterators
└── Makefile             # Build automation
