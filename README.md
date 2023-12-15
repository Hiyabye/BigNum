# Project BigNum

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

**Project BigNum** is a robust C++ implementation of an infinite integer class, designed for competitive programming contests. Its core functionality revolves around handling exceptionally large numbers with ease and precision.

## 🌟 Features

- **Infinite Size**: Utilizes `std::string` for representing numbers, offering virtually unlimited size.
- **Basic Operations**: Seamlessly performs addition, subtraction, multiplication, division, and modulo operations.
- **High Precision**: Maintains accuracy for extremely large calculations, a necessity in competitive programming.
- **Efficient Performance**: Optimized for quick computations, crucial for time-sensitive contests.

## 🛠 Installation

Integrating `BigNum` into your project is straightforward.

Just download and include the `BigNum.h` header file in your project.

```cpp
#include "BigNum.h"
```

For competitive programming, you can simply copy and paste the entire `BigNum` class into your contest file.

## 💡 Usage

Here's a quick example of how to use the `BigNum` class:

```cpp
#include <iostream>
#include "BigNum.h"

int main() {
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
- [ ] Implement advanced mathematical functions
- [ ] Optimize for even faster computations
- [ ] Extend support for additional number systems
- [ ] Develop a comprehensive suite of unit tests

## 🙌 Acknowledgements

Huge help from the following resources and communities:

- [readme.so](https://readme.so/) for README formatting tools.
 
## 📄 License

This project is open-sourced under the MIT License. See the [LICENSE](LICENSE) file for more details.
