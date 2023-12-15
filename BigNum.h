#pragma once

#include <iostream>
#include <string>

class BigNum {
private:
  std::string num;
  bool sign; // true: '+', false: '-'

  // Assume a >= b >= 0
  std::string add(std::string a, std::string b) const {
    // Edge cases
    if (a == "0") return b;
    if (b == "0") return a;

    // Threshold for simple addition
    if (a.length() <= 18 && b.length() <= 18) {
      return std::to_string(std::stoll(a) + std::stoll(b));
    }

    // Padding
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    // String addition
    std::string c = "";
    int carry = 0;
    for (int i=0; i<a.length() || i<b.length(); i++) {
      int aDigit = i < a.length() ? a[a.length()-i-1] - '0' : 0;
      int bDigit = i < b.length() ? b[b.length()-i-1] - '0' : 0;
      int sum = aDigit + bDigit + carry;
      carry = sum / 10;
      c = (char)(sum % 10 + '0') + c;
    }
    if (carry) c = (char)(carry + '0') + c;

    return c;
  }

  // Assume a >= b >= 0
  std::string sub(std::string a, std::string b) const {
    // Edge cases
    if (a == b) return "0";
    if (b == "0") return a;

    // Threshold for simple subtraction
    if (a.length() <= 18 && b.length() <= 18) {
      return std::to_string(std::stoll(a) - std::stoll(b));
    }

    // Padding
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    // String subtraction
    std::string c = "";
    int borrow = 0;
    for (int i=0; i<a.length(); i++) {
      int aDigit = a[a.length()-i-1] - '0';
      int bDigit = b[b.length()-i-1] - '0';
      int diff = aDigit - bDigit - borrow;
      borrow = diff < 0;
      c = (char)(diff + borrow * 10 + '0') + c;
    }

    // Remove leading zeros
    while (c[0] == '0') c = c.substr(1);

    return c;
  }

  // Assume a, b >= 0
  std::string mul(std::string a, std::string b) const {
    // Remove leading zeros
    while (a[0] == '0') a = a.substr(1);
    if (a == "") a = "0";
    while (b[0] == '0') b = b.substr(1);
    if (b == "") b = "0";

    // Edge cases
    if (a == "0" || b == "0") return "0";
    if (a == "1") return b;
    if (b == "1") return a;

    // Threshold for simple multiplication
    if (a.length() + b.length() <= 18) {
      return std::to_string(std::stoll(a) * std::stoll(b));
    }

    // Padding
    // TODO: Optimize padding
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    // Karatsuba algorithm
    int half = (a.length() > b.length() ? a.length() : b.length()) / 2;
    int aHalf = a.length() - half, bHalf = b.length() - half;
    std::string p1 = mul(a.substr(0, aHalf), b.substr(0, bHalf));
    std::string p2 = mul(a.substr(aHalf), b.substr(bHalf));
    std::string p3 = mul(add(a.substr(0, aHalf), a.substr(aHalf)), add(b.substr(0, bHalf), b.substr(bHalf)));
    std::string c = add(p1 + std::string(2 * half, '0'), p2);
    c = add(c, sub(p3, add(p1, p2)) + std::string(half, '0'));

    return c;
  }

  // Assume a, b >= 0
  std::string avg(std::string a, std::string b) const {
    // Threshold for simple average
    if (a.length() <= 18 && b.length() <= 18) {
      return std::to_string((std::stoll(a) + std::stoll(b)) / 2);
    }

    // String addition
    std::string sum = add(a, b);
    std::string c = sum;

    // Divide by 2
    int carry = 0;
    for (int i=0; i<sum.length(); i++) {
      int digit = sum[i] - '0';
      c[i] = (char)((digit + carry * 10) / 2 + '0');
      carry = (digit + carry * 10) % 2;
    }

    // Remove leading zeros
    while (c[0] == '0') c = c.substr(1);
    if (c == "") c = "0";

    return c;
  }

  // Assume a, b >= 0
  std::string div(const std::string &a, const std::string &b) const {
    // Edge cases
    if (a == "0") return "0";
    if (b == "0") throw "Division by zero";
    if (a == b) return "1";
    if (a.length() < b.length() || (a.length() == b.length() && a < b)) return "0";

    // Threshold for simple division
    if (a.length() <= 18 && b.length() <= 18) {
      return std::to_string(std::stoll(a) / std::stoll(b));
    }

    // Initial guess
    std::string r = "1";
    r += std::string(a.length() - b.length(), '0');

    // Newton's method
    std::string l = "1";
    std::string m = avg(l, r);
    while (l != m && m != r) {
      std::string p = mul(m, b);
      if (p.length() < a.length() || (p.length() == a.length() && p < a)) l = m;
      else if (p.length() > a.length() || (p.length() == a.length() && p > a)) r = m;
      else if (p == a) return m;
      m = avg(l, r);
    }

    // Correction step
    while (mul(m, b).length() < a.length() || (mul(m, b).length() == a.length() && mul(m, b) < a)) m = add(m, "1");
    while (mul(m, b).length() > a.length() || (mul(m, b).length() == a.length() && mul(m, b) > a)) m = sub(m, "1");

    return m;
  }

public:
  /* Constructors */
  BigNum(void) : num("0"), sign(true) {}
  BigNum(const BigNum &bn) : num(bn.num), sign(bn.sign) {}
  BigNum(const long long &n) : sign(n >= 0), num(std::to_string(n)) {}
  BigNum(const std::string &s) : sign(s[0] != '-'), num(s[0] == '-' ? s.substr(1) : s) {}

  /* Assignments */
  BigNum &operator=(const BigNum &bn) {
    num = bn.num;
    sign = bn.sign;
    return *this;
  }

  /* I/O */
  friend std::istream &operator>>(std::istream &is, BigNum &bn) {
    std::string s;
    is >> s;
    bn = BigNum(s);
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const BigNum &bn) {
    if (!bn.sign) os << '-';
    os << bn.num;
    return os;
  }

  /* Additions */
  BigNum operator+(const BigNum &bn) {
    BigNum res;

    if (this->sign == bn.sign) {
      res.sign = this->sign;
      res.num = add(this->num, bn.num);
    } else if (this->num > bn.num) {
      res.sign = this->sign;
      res.num = sub(this->num, bn.num);
    } else {
      res.sign = bn.sign;
      res.num = sub(bn.num, this->num);
    }
    
    return res;
  }

  BigNum operator+(const long long &n) {
    return *this + BigNum(n);
  }

  BigNum operator+(const std::string &s) {
    return *this + BigNum(s);
  }

  /* Subtractions */
  BigNum operator-(const BigNum &bn) {
    BigNum res;

    if (this->sign != bn.sign) {
      res.sign = this->sign;
      res.num = add(this->num, bn.num);
    } else if (*this >= bn) {
      res.sign = this->sign;
      res.num = sub(this->num, bn.num);
    } else {
      res.sign = !this->sign;
      res.num = sub(bn.num, this->num);
    }

    return res;
  }

  BigNum operator-(const long long &n) {
    return *this - BigNum(n);
  }

  BigNum operator-(const std::string &s) {
    return *this - BigNum(s);
  }

  /* Multiplications */
  BigNum operator*(const BigNum &bn) {
    BigNum res;

    res.sign = this->sign == bn.sign;
    res.num = mul(this->num, bn.num);

    return res;
  }

  BigNum operator*(const long long &n) {
    return *this * BigNum(n);
  }

  BigNum operator*(const std::string &s) {
    return *this * BigNum(s);
  }

  /* Divisions */
  BigNum operator/(const BigNum &bn) {
    BigNum res;

    res.sign = this->sign == bn.sign;
    res.num = div(this->num, bn.num);

    return res;
  }

  BigNum operator/(const long long &n) {
    return *this / BigNum(n);
  }

  BigNum operator/(const std::string &s) {
    return *this / BigNum(s);
  }

  /* Modulos */
  BigNum operator%(const BigNum &bn) {
    BigNum res;

    // Edge cases
    if (bn.num == "0") throw "Division by zero";
    if (this->num == "0") return BigNum(0);

    // Main cases
    return *this - (*this / bn) * bn;
  }

  BigNum operator%(const long long &n) {
    return *this % BigNum(n);
  }

  BigNum operator%(const std::string &s) {
    return *this % BigNum(s);
  }

  /* Comparisons */
  bool operator==(const BigNum &bn) {
    return this->num == bn.num && this->sign == bn.sign;
  }

  bool operator==(const long long &n) {
    return *this == BigNum(n);
  }

  bool operator==(const std::string &s) {
    return *this == BigNum(s);
  }

  bool operator!=(const BigNum &bn) {
    return !(*this == bn);
  }

  bool operator!=(const long long &n) {
    return !(*this == n);
  }

  bool operator!=(const std::string &s) {
    return !(*this == s);
  }

  bool operator<(const BigNum &bn) {
    if (this->sign != bn.sign) return !this->sign;
    if (this->num.length() != bn.num.length()) return this->num.length() < bn.num.length();
    return this->num < bn.num;
  }

  bool operator<(const long long &n) {
    return *this < BigNum(n);
  }

  bool operator<(const std::string &s) {
    return *this < BigNum(s);
  }

  bool operator<=(const BigNum &bn) {
    return *this < bn || *this == bn;
  }

  bool operator<=(const long long &n) {
    return *this < n || *this == n;
  }

  bool operator<=(const std::string &s) {
    return *this < s || *this == s;
  }

  bool operator>(const BigNum &bn) {
    return !(*this <= bn);
  }

  bool operator>(const long long &n) {
    return !(*this <= n);
  }

  bool operator>(const std::string &s) {
    return !(*this <= s);
  }

  bool operator>=(const BigNum &bn) {
    return !(*this < bn);
  }

  bool operator>=(const long long &n) {
    return !(*this < n);
  }

  bool operator>=(const std::string &s) {
    return !(*this < s);
  }
};