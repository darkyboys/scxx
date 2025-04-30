# `alph` Data Type Documentation
### Scxx Standard Type - `alph`
---

## Overview

The `alph` type is a **low-level custom dynamic character array** implementation for the Scxx framework.

It is designed to work in **any C++ environment**, even inside a **minimal operating system kernel**, as long as basic dynamic memory management (e.g., `new` and `delete[]`) is available.

- **No external libraries** used (no `<string>`, `<vector>`, etc.)
- **Manual memory management** (direct control over heap allocations)
- **Lightweight and portable**, suitable for **kernel-level** or **embedded systems**.

`alph` provides:
- Dynamic string storage (`char*`)
- String copying and modifying
- Substring extraction
- Searching
- Appending
- Manual memory control

---

## Kernel Suitability

`alph` is designed to be **independent** from any runtime environment except the basic C++ heap (`new`, `delete[]`).

It can be safely used in **kernel development** under the following conditions:
- The kernel provides a working **Memory Management Unit (MMU)** and heap allocator.
- The `new` and `delete[]` operators are available (custom or native).
- No exceptions or high-level library functions are required.

Thus, `alph` is ideal for **bare-metal programming**, **low-level C++ projects**, and **custom OS development**.

---

## Licensing

```
Copyright (c) ghgltggamer 2025
Written by ghgltggamer
Licensed under the MIT License
```
For more details, refer to the `README.md`.

---

## Basic Usage

```cpp
#include "scxx_alph.hpp" // or your correct header path

alph mystring("Hello Kernel!");

char* val = mystring.value(); // returns the internal string
unsigned long long len = mystring.length; // returns length

unsigned long long pos = mystring.find("Kernel"); // find substring
char* sub = mystring.substr(6, 6); // get "Kernel"

mystring.append(" Development"); // append more text

char ch = mystring.at(0); // access character at position 0

delete[] sub; // remember to delete substrings you allocate!
```

---

## Constructor

```cpp
alph (const char* __VALUE);
```
Creates a new `alph` object initialized with the given C-string (`const char*`).

- Allocates and copies the input string.
- Updates internal metadata (`length`).

---

## Methods

### `.value(const char* __VALUE = "\0") -> char*`
- **Getter**: returns the current internal value if no argument is passed.
- **Setter**: replaces internal storage with the given `const char*`.
- Updates `length` automatically.

---

### `.find(const char* __VALUE, unsigned long long pos = 0, unsigned long long skips = 0) -> unsigned long long`
- Searches for the first (or skipped) occurrence of a substring starting from position `pos`.
- Returns the found position or `UNIDEF` (`-1`) if not found.

---

### `.substr(unsigned long long start = 0, unsigned long long len = -1) -> char*`
- Extracts a substring from `start` for `len` characters.
- If `len == -1`, extracts until the end.
- If out-of-bounds, safe behavior is applied (`substr_out_of_bounds` is set).
- **Returned pointer must be manually deleted**.

---

### `.append(const char* what) -> void`
- Appends the `what` C-string to the existing internal value.
- Memory is resized and copied manually.

---

### `.at(unsigned long long index) -> char`
- Returns the character at the specified `index`.
- If index is invalid, returns an undefined special value (`UNIDEF - '0'`).

---

## Public Fields

| Field | Type | Description |
|:---|:---|:---|
| `length` | `unsigned long long` | Length of the current value. |
| `UNIDEF` | `const unsigned long long` | Represents an undefined result (`-1`). |
| `substr_out_of_bounds` | `bool` | Set `true` if `.substr()` detects out-of-bounds start. |

---

## Memory Management Notes

- `.substr()` allocates new memory. Always `delete[]` the returned pointer manually.
- `.value()` returns the internal pointer. Do **NOT** delete it manually.
- `.value(new_string)` automatically deletes old internal memory and replaces it.
- Destructor `~alph()` automatically frees internal memory.

---

## Example Program

```cpp
#include "scxx_alph.hpp"
#include <iostream>

int main() {
    alph kernel_str("Kernel");

    kernel_str.append(" Programming");
    std::cout << "Kernel String: " << kernel_str.value() << std::endl;
    std::cout << "Length: " << kernel_str.length << std::endl;

    unsigned long long position = kernel_str.find("Programming");
    std::cout << "'Programming' starts at: " << position << std::endl;

    char* part = kernel_str.substr(7, 11); // "Programming"
    std::cout << "Substring: " << part << std::endl;

    delete[] part; // Important!

    return 0;
}
```

---

## Known Limitations

- No UTF-8 or Unicode support.
- No automatic memory management (manual `delete[]` needed).
- No exception handling (out-of-bounds or allocation failures are not caught).
- `at(index)` returns an invalid value, not an exception, on out-of-bounds access.

---

# Summary

The `alph` datatype is a **low-level**, **self-contained**, and **kernel-ready** lightweight string handler.  
It is ideal for:
- OS kernels
- Bare-metal systems
- Embedded C++ environments
- High-performance low-level libraries

It is minimal, reliable, and fully manual — perfect for real developers who **want full control over memory and execution**.


--- 


# str.md

# str - Mid-Level Dynamic String Class for Scxx

---

## Overview

`str` is a **mid-level dynamic string type** in Scxx, built directly on top of the low-level `alph` datatype.
It provides user-friendly operations like appending, finding, substring extraction, and replacing text,
without relying on any part of the C++ Standard Library (STL) beyond basic memory operations.

> **Note:** Since `str` internally uses `alph`, it is lightweight, heap-based, and kernel-safe **if basic memory management is available** (e.g., `new`, `delete`).

`str` is ideal for projects that need a flexible, dynamic string but do not want the overhead of full STL containers like `std::string`.

---

## Features

- Dynamic string creation and management
- Safe appending of characters and strings
- Character access with bounds checking fallback
- Substring extraction with error handling
- Find operations (including skip-counting)
- Replace first occurrence or all occurrences of a substring
- Minimal memory footprint, STL-free

---

## How to Use

### Creating a `str`
```cpp
str s("Hello World");
```

### Accessing and Setting the Value
```cpp
// Get the value
char* val = s.value();

// Set a new value
s.value("New Value");
```

### Appending Text
```cpp
s.append("!");
```

or using an alias:
```cpp
s.concat(" More text.");
```

### Accessing Characters
```cpp
char c = s.at(1); // returns 'e'
```

If you request an index out of bounds, it returns a special invalid value based on `UNIDEF`.

### Finding Substrings
```cpp
unsigned long long pos = s.find("World", 0, 0);
// pos will contain the starting index of "World"
```

### Getting a Substring
```cpp
char* sub = s.substr(6, 5); // returns "World"
```

If you attempt to substring out of bounds, `substr_out_of_bounds` is set to `true`.

### Replacing Substrings
```cpp
char* replaced = s.replace("World", "Everyone");
```

### Replacing All Occurrences
```cpp
char* replaced_all = s.replaceAll("l", "L");
```

### Getting the Size
```cpp
unsigned long long size = s.size();
// Note: returns length - 1
```

---

## Technical Details

- **Heap-Based:** All operations allocate/deallocate manually using `new` and `delete`.
- **No STL:** No `std::string`, `std::vector`, or similar containers are used.
- **Depends on `alph`:** `str` wraps an internal `alph` instance and forwards most operations.
- **UNIDEF Constant:** Used internally to represent invalid or "undefined" results.
- **Memory Management:** Users should be cautious when working with returned `char*` to avoid leaks.

---

## Why Use `str`?

- Perfect for low-level, lightweight operating systems.
- Can be safely used inside kernels that provide a basic memory management unit (MMU).
- No external library or dependency required.
- Provides familiar high-level string operations while staying close to the hardware.

---

## License

```
MIT License
Copyright (c) ghgltggamer 2025
```

See [README.md](./README.md) for more details.

---

> Written with care for low-level enthusiasts and system developers.

---

# Summary

`str` gives you a flexible, dynamic, mid-level string abstraction — easy to use, but still completely under your control.

If you need **full control** like bare-metal programming but also want **ease of manipulation**, `str` is made for you.

