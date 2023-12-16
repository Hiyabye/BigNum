# Project BigNum

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

**Project BigNum** is a robust C++ implementation of an infinite integer class, designed for competitive programming contests. Its core functionality revolves around handling exceptionally large numbers with ease and precision.

## 🌟 Features

- **Infinite Size**: Utilizes `std::string` for representing numbers, offering virtually unlimited size.
- **Basic Operations**: Seamlessly performs addition, subtraction, multiplication, division, and modulo operations.
- **High Precision**: Maintains accuracy for extremely large calculations, a necessity in competitive programming.
- **Efficient Performance**: Optimized for quick computations, crucial for time-sensitive contests.

## 🛠 Installation

Integrating `BigNum` into your project can be done based on your needs.

### 📦 Using CMake

If you're using CMake, you can simply add `BigNum` as a dependency in your `CMakeLists.txt` file.

```cmake
add_subdirectory(BigNum)
target_link_libraries(<your-target> BigNum)
```

### 👑 Competitve Programming

For competitive programming, you can simply use the `BigNum-contest.cpp` file as a starting point for your contest file. This file contains the entire `BigNum` class, along with a few other useful functions.

## 💡 Usage

Here's a quick example of how to use the `BigNum` class:

```cpp
#include <iostream>
#include "BigNum.h"

int main(void) {
  BigNum a("123456789012345678901234567890");
  BigNum b("987654321098765432109876543210");

  BigNum c = a + b;
  std::cout << c << std::endl;
  
  return 0;
}
```

## 📚 Examples

Discover more about how `BigNum` can be used in the `examples` directory. Each example provides practical use-cases to help you understand the capabilities of `BigNum`.

## 🗺️ Roadmap

To continuously improve `BigNum`, our roadmap includes:

- [x] Implement basic arithmetic operations
- [x] Implement comparison operators
- [x] Implement input and output operators
- [x] Modularize code into separate files
- [x] CMake support
- [x] Develop a comprehensive suite of unit tests using Google Test
- [ ] Implement advanced mathematical functions
  - [x] GCD and LCM
  - [x] Absolute value
  - [x] Power
  - [ ] Square root
  - [ ] Logarithm
  - [ ] Trigonometric functions
- [ ] Improve memory management
- [ ] Improve error handling
- [ ] Optimize for even faster computations
- [ ] Improve documentation using Doxygen
- [ ] Extend support for additional number systems
- [ ] Extend support for additional data types

## 🙌 Acknowledgements

Huge help from the following resources and communities:

- [readme.so](https://readme.so/) for README formatting tools.
- [shields.io](https://shields.io/) for badges.
- [gitignore.io](https://www.toptal.com/developers/gitignore) for `.gitignore` files.
- [Google Test](https://github.com/google/googletest) for unit testing.

## 📄 License

This project is open-sourced under the MIT License. See the [LICENSE](LICENSE) file for more details.
