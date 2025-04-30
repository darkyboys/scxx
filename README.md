# SCxx Library

> **Simple, Clean, and eXtendable types for C++**

---

## About

**SCxx** is a lightweight, low-overhead header-only library providing simple data types that work at both **low-level** and **mid-level** programming. It is designed for developers who want full control over their data structures without the complexity or bloat of larger frameworks.

It mainly provides:

- `alph`: a low-level, MMU-friendly, dynamic character array type
- `str`: a mid-level, string-like type with higher usability and convenience

The goal of SCxx is to give **C++ developers** easy-to-use, efficient types directly by simply including one header.

---

## Usage

Simply include the main SCxx header into your project:

```cpp
#include "scxx/scxx.hh"
```

No build system setup, no installations, no package managers. Just a local, clean header you control.

---

## Types Provided

### 1. `alph`

- **Type**: Low-Level
- **Description**:
  - Basic, dynamically allocated character array.
  - Lightweight and directly usable even in a kernel environment (only needs basic MMU support).
  - No dependency on the standard library apart from very basic memory operations.
- **Key Features**:
  - Copy and manage `char*` manually.
  - Perform substring extraction, character access, basic find operations.
  - Minimal memory overhead.

### 2. `str`

- **Type**: Mid-Level
- **Description**:
  - Built on top of `alph` for more usability.
  - Behaves more like a lightweight `std::string` but maintains low-level efficiency.
  - Designed for applications needing flexibility without losing performance.
- **Key Features**:
  - Easy append, find, replace, substring operations.
  - Dynamically updates its internal storage based on operations.
  - Still very lightweight compared to high-level containers.

More types will be added in future updates!

---

## Example

```cpp
#include "scxx/scxx.hh"
#include <iostream>

int main() {
    str myStr("Hello");
    myStr.append(", World!");

    std::cout << myStr.value() << std::endl; // Output: Hello, World!

    unsigned long long found = myStr.find("World");
    if (found != myStr.UNIDEF) {
        std::cout << "Found at position: " << found << std::endl;
    }

    char* replaced = myStr.replace("World", "SCxx");
    std::cout << replaced << std::endl; // Output: Hello, SCxx!

    delete[] replaced; // Manual memory management

    return 0;
}
```

---

## Why Use SCxx?

- **Header-Only**: No builds, no binaries.
- **Minimalist**: Extremely lightweight.
- **Extendable**: Easy to create your own types on top of `alph` and `str`.
- **Low-Level Friendly**: Can be used in bare-metal environments.
- **Developer Freedom**: No hidden behavior, you control memory.

---

## Repository

Official GitHub: [https://github.com/darkyboys/scxx](https://github.com/darkyboys/scxx)

> Contributions are welcome! Feel free to fork, suggest improvements, or report issues.

---

## Documentation

You can find type documentation [here](docs.md).

---

## License

This project is licensed under the [MIT License](LICENSE).

> Written with ❤️ by **ghgltggamer** 2025.

SCxx stands for **Simple Cxx (C++)**.
