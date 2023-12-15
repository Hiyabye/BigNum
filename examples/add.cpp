#include <iostream>
#include "BigNum.h"

int main(void) {
  BigNum a("123456789012345678901234567890");
  BigNum b("987654321098765432109876543210");

  BigNum c = a + b;
  std::cout << c << std::endl;
  
  return 0;
}