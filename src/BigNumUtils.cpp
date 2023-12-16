#include "BigNum.h"
#include "BigNumUtils.h"

/**
 * @brief Greatest common divisor
 * @details Assume a, b are non-negative
 * @param a First number
 * @param b Second number
 * @return Greatest common divisor of a and b
 * @see https://en.wikipedia.org/wiki/Euclidean_algorithm
 * @todo Support decimal numbers
*/
BigNum gcd(BigNum a, BigNum b) {
  while (b != 0) {
    BigNum r = a % b;
    a = b;
    b = r;
  }
  return a;
}

/**
 * @brief Least common multiple
 * @details Assume a, b are non-negative
 * @param a First number
 * @param b Second number
 * @return Least common multiple of a and b
 * @see https://en.wikipedia.org/wiki/Least_common_multiple
 * @todo Support decimal numbers
*/
BigNum lcm(BigNum &a, BigNum &b) {
  return a / gcd(a, b) * b;
}

/**
 * @brief Absolute value
 * @details Assume bn is non-negative
 * @param bn Big number
 * @return Absolute value of bn
 * @see https://en.wikipedia.org/wiki/Absolute_value
 * @todo Support decimal numbers
*/
BigNum abs(const BigNum &bn) {
  return BigNum(true, bn.num);
}

/**
 * @brief Power function
 * @details Assume base, exp are non-negative
 * @param base Base
 * @param exp Exponent
 * @return base ^ exp
 * @see https://en.wikipedia.org/wiki/Exponentiation_by_squaring
 * @todo Support decimal numbers
*/
BigNum pow(BigNum base, BigNum exp) {
  BigNum res(1LL);
  while (exp > 0) {
    if (exp % 2 == 1) res *= base;
    base *= base;
    exp /= 2;
  }
  return res;
}