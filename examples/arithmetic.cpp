#include <iostream>
#include "BigNum.h"

using namespace std;

int main(void) {
  BigNum a("987654321098765432109876543210");
  BigNum b("123456789012345678901234567890");

  // Addition
  BigNum c = a + b;
  cout << c << endl; // 1111111110111111111011111111100

  // Subtraction
  BigNum d = a - b;
  cout << d << endl; // 864197532086419753208641975320

  // Multiplication
  BigNum e = a * b;
  cout << e << endl; // 121932631137021795226185032733622923332237463801111263526900

  // Division
  BigNum f = a / b;
  cout << f << endl; // 8

  // Modulus
  BigNum g = a % b;
  cout << g << endl; // 9000000000900000000090
  
  return 0;
}