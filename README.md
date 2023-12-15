# Project BigNum

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

A C++ implementation of an infinite integer class designed for competitive programming contests, where handling large numbers is essential.

## Features

- Based on std::string, providing almost unlimited size.
- Supports basic operations: addition, subtraction, multiplication, division, and modulo.

## Installation

To use this library in your project, include the header file `BigNum.h`.

```cpp
#include "BigNum.h"
```

For competitive programming contests, you can copy the entire class and paste it into a single file.

## Usage

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

## Examples

You can find more usage examples in the `examples` directory of this repository.

## Acknowledgements

- [readme.so](https://readme.so/)
 
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
