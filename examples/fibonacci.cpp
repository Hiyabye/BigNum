#include <iostream>
#include <vector>
#include "BigNum.h"

using namespace std;

int main(void) {
  // Initialize the first two numbers of the Fibonacci sequence
  vector<BigNum> fib(101);
  fib[0] = BigNum("0");
  fib[1] = BigNum("1");

  // Calculate the rest of the Fibonacci sequence
  for (int i = 2; i <= 100; ++i) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  // Print the 100th Fibonacci number
  cout << fib[100] << endl; // 354224848179261915075

  return 0;
}