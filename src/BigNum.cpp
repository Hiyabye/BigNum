#include "BigNum.h"

////////// Constructors //////////

BigNum::BigNum(void) : num("0"), sign(true) {}
BigNum::BigNum(const BigNum &bn) : num(bn.num), sign(bn.sign) { trim(this->num); }
BigNum::BigNum(const long long &n) : sign(n >= 0), num(std::to_string(n)) { trim(this->num); }
BigNum::BigNum(const long double &n) : sign(n >= 0), num(std::to_string(n)) { trim(this->num); }
BigNum::BigNum(const std::string &s) : sign(s[0] != '-'), num(s[0] == '-' ? s.substr(1) : s) { trim(this->num); }
BigNum::BigNum(const bool &s, const std::string &n) : sign(s), num(n) { trim(this->num); }

////////// Input & Output //////////

std::istream &operator>>(std::istream &is, BigNum &bn) {
  std::string s;
  is >> s;
  bn = BigNum(s);
  return is;
}

std::ostream &operator<<(std::ostream &os, const BigNum &bn) {
  if (!bn.sign) os << '-';
  os << bn.num;
  return os;
}

////////// Assignment operators //////////

BigNum &BigNum::operator=(const BigNum &bn) {
  if (this != &bn) {
    this->sign = bn.sign;
    this->num = bn.num;
  }
  return *this;
}
BigNum &BigNum::operator=(const long long &n) { return *this = BigNum(n); }
BigNum &BigNum::operator=(const std::string &s) { return *this = BigNum(s); }

////////// Addition operators //////////

BigNum BigNum::operator+(const BigNum &bn) {
  if (this->sign == bn.sign) return BigNum(this->sign, add(this->num, bn.num));
  else if (*this >= bn)      return BigNum(this->sign, sub(this->num, bn.num));
  else                       return BigNum(!this->sign, sub(bn.num, this->num));
}
BigNum BigNum::operator+(const long long &n) { return *this + BigNum(n); }
BigNum BigNum::operator+(const std::string &s) { return *this + BigNum(s); }
BigNum BigNum::operator+=(const BigNum &bn) { return *this = *this + bn; }
BigNum BigNum::operator+=(const long long &n) { return *this = *this + n; }
BigNum BigNum::operator+=(const std::string &s) { return *this = *this + s; }

////////// Subtraction operators //////////

BigNum BigNum::operator-(const BigNum &bn) {
  if (this->sign != bn.sign) return BigNum(this->sign, add(this->num, bn.num));
  else if (*this >= bn)      return BigNum(this->sign, sub(this->num, bn.num));
  else                       return BigNum(!this->sign, sub(bn.num, this->num));
}
BigNum BigNum::operator-(const long long &n) { return *this - BigNum(n); }
BigNum BigNum::operator-(const std::string &s) { return *this - BigNum(s); }
BigNum BigNum::operator-=(const BigNum &bn) { return *this = *this - bn; }
BigNum BigNum::operator-=(const long long &n) { return *this = *this - n; }
BigNum BigNum::operator-=(const std::string &s) { return *this = *this - s; }

////////// Multiplication operators //////////

BigNum BigNum::operator*(const BigNum &bn) { return BigNum(this->sign == bn.sign, mul(this->num, bn.num)); }
BigNum BigNum::operator*(const long long &n) { return *this * BigNum(n); }
BigNum BigNum::operator*(const std::string &s) { return *this * BigNum(s); }
BigNum BigNum::operator*=(const BigNum &bn) { return *this = *this * bn; }
BigNum BigNum::operator*=(const long long &n) { return *this = *this * n; }
BigNum BigNum::operator*=(const std::string &s) { return *this = *this * s; }

////////// Division operators //////////

BigNum BigNum::operator/(const BigNum &bn) { return BigNum(this->sign == bn.sign, div(this->num, bn.num)); }
BigNum BigNum::operator/(const long long &n) { return *this / BigNum(n); }
BigNum BigNum::operator/(const std::string &s) { return *this / BigNum(s); }
BigNum BigNum::operator/=(const BigNum &bn) { return *this = *this / bn; }
BigNum BigNum::operator/=(const long long &n) { return *this = *this / n; }
BigNum BigNum::operator/=(const std::string &s) { return *this = *this / s; }

////////// Modulo operators //////////

BigNum BigNum::operator%(const BigNum &bn) { return *this - (*this / bn) * bn; }
BigNum BigNum::operator%(const long long &n) { return *this % BigNum(n); }
BigNum BigNum::operator%(const std::string &s) { return *this % BigNum(s); }
BigNum BigNum::operator%=(const BigNum &bn) { return *this = *this % bn; }
BigNum BigNum::operator%=(const long long &n) { return *this = *this % n; }
BigNum BigNum::operator%=(const std::string &s) { return *this = *this % s; }

////////// Comparison operators //////////

bool BigNum::operator==(const BigNum &bn) const { return this->num == bn.num && this->sign == bn.sign; }
bool BigNum::operator==(const long long &n) const { return *this == BigNum(n); }
bool BigNum::operator==(const std::string &s) const { return *this == BigNum(s); }
bool BigNum::operator!=(const BigNum &bn) const { return !(*this == bn); }
bool BigNum::operator!=(const long long &n) const { return !(*this == n); }
bool BigNum::operator!=(const std::string &s) const { return !(*this == s); }
bool BigNum::operator<(const BigNum &bn) const { return this->sign != bn.sign ? !this->sign : this->num.length() != bn.num.length() ? this->num.length() < bn.num.length() : this->num < bn.num; }
bool BigNum::operator<(const long long &n) const { return *this < BigNum(n); }
bool BigNum::operator<(const std::string &s) const { return *this < BigNum(s); }
bool BigNum::operator<=(const BigNum &bn) const { return *this < bn || *this == bn; }
bool BigNum::operator<=(const long long &n) const { return *this < n || *this == n; }
bool BigNum::operator<=(const std::string &s) const { return *this < s || *this == s; }
bool BigNum::operator>(const BigNum &bn) const { return !(*this <= bn); }
bool BigNum::operator>(const long long &n) const { return !(*this <= n); }
bool BigNum::operator>(const std::string &s) const { return !(*this <= s); }
bool BigNum::operator>=(const BigNum &bn) const { return !(*this < bn); }
bool BigNum::operator>=(const long long &n) const { return !(*this < n); }
bool BigNum::operator>=(const std::string &s) const { return !(*this < s); }

////////// Helper functions //////////

/**
 * @brief Trim leading and trailing zeros
 * @details Assume s is non-negative as we process sign separately
 *          This function is used in add, sub, mul, avg
 * @param s String to be trimmed
*/
void BigNum::trim(std::string &s) {
  // Remove leading zeros
  int lead = s.find_first_not_of('0');
  s = (lead != std::string::npos) ? s.substr(lead) : "0";

  // Based on the decimal point, remove trailing zeros
  int dot = s.find_first_of('.');
  if (dot != std::string::npos) {
    int trail = s.find_last_not_of('0');
    s = (trail != std::string::npos) ? s.substr(0, trail + 1) : "0";
    if (s.back() == '.') s.pop_back();
  }
}

/**
 * @brief Pad a and b to the same length
 * @details Assume a, b are non-negative
 *          This function is used in add, sub, mul
 * @param a First string
 * @param b Second string
*/
void BigNum::padding(std::string &a, std::string &b) {
  // Find the decimal point
  int dotA = a.find_first_of('.'), dotB = b.find_first_of('.');
  if (dotA == std::string::npos) dotA = a.length();
  if (dotB == std::string::npos) dotB = b.length();

  // Pad zeros in back
  if (dotA != a.length() || dotB != b.length()) {
    if (a.length() - dotA > b.length() - dotB) {
      if (dotB == b.length()) b.push_back('.');
      b.append(std::string(a.length() - dotA - b.length() + dotB, '0'));
    }
    if (a.length() - dotA < b.length() - dotB) {
      if (dotA == a.length()) a.push_back('.');
      a.append(std::string(b.length() - dotB - a.length() + dotA, '0'));
    }
  }

  // Pad zeros in front
  if (dotA > dotB) b.insert(0, std::string(dotA - dotB, '0'));
  if (dotA < dotB) a.insert(0, std::string(dotB - dotA, '0'));
}

////////// Basic operations //////////

/**
 * @brief Add two strings digit by digit
 * @details Assume a, b are non-negative and a >= b
 * @param a First string
 * @param b Second string
 * @return Sum of a and b
 * @todo Support threshold for simple addition
*/
std::string BigNum::add(std::string a, std::string b) {
  padding(a, b);

  // String addition
  std::string c = "";
  int carry = 0, sum = 0;
  for (int i = a.length() - 1; i >= 0; --i) {
    if (a[i] == '.') {
      c.insert(0, 1, '.');
      continue;
    }
    sum = (a[i] - '0') + (b[i] - '0') + carry;
    carry = sum / 10;
    c.insert(0, 1, (char)(sum % 10 + '0'));
  }
  if (carry) c.insert(0, 1, (char)(carry + '0'));
  trim(c);

  return c;
}

/**
 * @brief Subtract two strings digit by digit
 * @details Assume a, b are non-negative and a >= b
 * @param a First string
 * @param b Second string
 * @return Difference of a and b
 * @todo Support threshold for simple subtraction
*/
std::string BigNum::sub(std::string a, std::string b) {
  padding(a, b);

  // String subtraction
  std::string c = "";
  int borrow = 0, diff = 0;
  for (int i = a.length() - 1; i >= 0; --i) {
    if (a[i] == '.') {
      c.insert(0, 1, '.');
      continue;
    }
    diff = (a[i] - '0') - (b[i] - '0') - borrow;
    borrow = diff < 0 ? 1 : 0;
    c.insert(0, 1, (char)(diff + borrow * 10 + '0'));
  }
  trim(c);

  return c;
}

/**
 * @brief Implementation of Karatsuba algorithm
 * @details Divide and conquer algorithm for fast multiplication
 *          Assume a, b are non-negative and integers
 * @param a First string
 * @param b Second string
 * @return Product of a and b
 * @see https://en.wikipedia.org/wiki/Karatsuba_algorithm
*/
std::string BigNum::karatsuba(std::string a, std::string b) {
  // Threshold for simple multiplication
  if (a.length() <= 18 && b.length() <= 18) {
    return std::to_string(std::stoll(a) * std::stoll(b));
  }

  int half = (a.length() > b.length() ? a.length() : b.length()) >> 1;
  int aHalf = a.length() - half, bHalf = b.length() - half;
  std::string p1 = karatsuba(a.substr(0, aHalf), b.substr(0, bHalf));
  std::string p2 = karatsuba(a.substr(aHalf), b.substr(bHalf));
  std::string p3 = karatsuba(add(a.substr(0, aHalf), a.substr(aHalf)), add(b.substr(0, bHalf), b.substr(bHalf)));
  std::string c = add(p1 + std::string(half << 1, '0'), p2);
  c = add(c, sub(p3, add(p1, p2)) + std::string(half, '0'));
  trim(c);

  return c;
}

/**
 * @brief Multiply two strings using Karatsuba algorithm
 * @details Assume a, b are non-negative
 * @param a First string
 * @param b Second string
 * @return Product of a and b
 * @todo Support threshold for simple multiplication
*/
std::string BigNum::mul(std::string a, std::string b) {
  // Remove leading zeros
  trim(a);
  trim(b);

  int dotA = a.find_first_of('.'), dotB = b.find_first_of('.');
  if (dotA == std::string::npos) dotA = a.length();
  if (dotB == std::string::npos) dotB = b.length();

  int decimalA = a.length() - dotA, decimalB = b.length() - dotB;
  if (dotA != a.length()) { decimalA--; a.erase(dotA, 1); }
  if (dotB != b.length()) { decimalB--; b.erase(dotB, 1); }

  std::string c = karatsuba(a, b);
  int decimalC = decimalA + decimalB;
  int dotC = c.length() - decimalC;

  if (dotC > 0) c.insert(dotC, 1, '.');
  trim(c);

  return c;
}

/**
 * @brief Average two strings
 * @details Assume a, b are non-negative
 *          Helper function for div
 * @param a First string
 * @param b Second string
 * @return Average of a and b
 * @todo Support decimal numbers
*/
std::string BigNum::avg(const std::string &a, const std::string &b) {
  // Threshold for simple average
  if (a.length() <= 18 && b.length() <= 18) {
    return std::to_string((std::stoll(a) + std::stoll(b)) >> 1);
  }

  // String addition
  std::string sum = add(a, b);
  std::string c = sum;

  // Divide by 2
  int carry = 0;
  for (int i = 0; i < sum.length(); ++i) {
    int digit = sum[i] - '0';
    c[i] = (char)(((digit + carry * 10) >> 1) + '0');
    carry = (digit + carry * 10) & 1;
  }
  trim(c);

  return c;
}

/**
 * @brief Divide two strings using Newton-Raphson method
 * @details Assume a, b are non-negative
 * @param a First string
 * @param b Second string
 * @return Quotient of a and b
 * @throws Division by zero
 * @see https://en.wikipedia.org/wiki/Division_algorithm#Newton.E2.80.93Raphson_division
 * @todo Support decimal numbers
*/
std::string BigNum::div(const std::string &a, const std::string &b) {
  // Edge cases
  if (b == "0") throw "Division by zero";
  if (a == "0" || a.length() < b.length() || (a.length() == b.length() && a < b)) return "0";

  // Threshold for simple division
  if (a.length() <= 18 && b.length() <= 18) {
    return std::to_string(std::stoll(a) / std::stoll(b));
  }

  // Initial guess - 10 ^ (a.length() - b.length())
  std::string r = "1";
  r += std::string(a.length() - b.length() + 1, '0');

  // Newton-Raphson method
  std::string l = "1";
  std::string m = avg(l, r);
  while (l != m && m != r) {
    std::string p = mul(m, b);
    if (p.length() < a.length() || (p.length() == a.length() && p < a)) l = m;
    else if (p.length() > a.length() || (p.length() == a.length() && p > a)) r = m;
    else if (p == a) return m;
    m = avg(l, r);
  }

  // Correction step - without this step, the result may be off by 1
  while (mul(m, b).length() < a.length() || (mul(m, b).length() == a.length() && mul(m, b) < a)) m = add(m, "1");
  while (mul(m, b).length() > a.length() || (mul(m, b).length() == a.length() && mul(m, b) > a)) m = sub(m, "1");

  return m;
}