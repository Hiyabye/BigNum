#pragma once

#include <iostream>
#include <string>

class BigNum {
public:
  std::string num;
  bool sign; // true: '+', false: '-'

  // Constructors
  BigNum(void);
  BigNum(const BigNum &bn);
  BigNum(const long long &n);
  BigNum(const long double &n);
  BigNum(const std::string &s);
  BigNum(const bool &s, const std::string &n);

  // Input & Output
  friend std::istream &operator>>(std::istream &is, BigNum &bn);
  friend std::ostream &operator<<(std::ostream &os, const BigNum &bn);
  
  // Assignment operators
  BigNum &operator=(const BigNum &bn);
  BigNum &operator=(const long long &n);
  BigNum &operator=(const std::string &s);

  // Addition operators
  BigNum operator+(const BigNum &bn);
  BigNum operator+(const long long &n);
  BigNum operator+(const std::string &s);
  BigNum operator+=(const BigNum &bn);
  BigNum operator+=(const long long &n);
  BigNum operator+=(const std::string &s);

  // Subtraction operators
  BigNum operator-(const BigNum &bn);
  BigNum operator-(const long long &n);
  BigNum operator-(const std::string &s);
  BigNum operator-=(const BigNum &bn);
  BigNum operator-=(const long long &n);
  BigNum operator-=(const std::string &s);

  // Multiplication operators
  BigNum operator*(const BigNum &bn);
  BigNum operator*(const long long &n);
  BigNum operator*(const std::string &s);
  BigNum operator*=(const BigNum &bn);
  BigNum operator*=(const long long &n);
  BigNum operator*=(const std::string &s);

  // Division operators
  BigNum operator/(const BigNum &bn);
  BigNum operator/(const long long &n);
  BigNum operator/(const std::string &s);
  BigNum operator/=(const BigNum &bn);
  BigNum operator/=(const long long &n);
  BigNum operator/=(const std::string &s);

  // Modulo operators
  BigNum operator%(const BigNum &bn);
  BigNum operator%(const long long &n);
  BigNum operator%(const std::string &s);
  BigNum operator%=(const BigNum &bn);
  BigNum operator%=(const long long &n);
  BigNum operator%=(const std::string &s);

  // Comparison operators
  bool operator==(const BigNum &bn) const;
  bool operator==(const long long &n) const;
  bool operator==(const std::string &s) const;
  bool operator!=(const BigNum &bn) const;
  bool operator!=(const long long &n) const;
  bool operator!=(const std::string &s) const;
  bool operator<(const BigNum &bn) const;
  bool operator<(const long long &n) const;
  bool operator<(const std::string &s) const;
  bool operator<=(const BigNum &bn) const;
  bool operator<=(const long long &n) const;
  bool operator<=(const std::string &s) const;
  bool operator>(const BigNum &bn) const;
  bool operator>(const long long &n) const;
  bool operator>(const std::string &s) const;
  bool operator>=(const BigNum &bn) const;
  bool operator>=(const long long &n) const;
  bool operator>=(const std::string &s) const;

  // Helper functions
  void trim(std::string &s);
  void padding(std::string &a, std::string &b);

  // Basic operations
  std::string add(std::string a, std::string b);
  std::string sub(std::string a, std::string b);
  std::string karatsuba(std::string a, std::string b);
  std::string mul(std::string a, std::string b);
  std::string avg(const std::string &a, const std::string &b);
  std::string div(const std::string &a, const std::string &b);
};