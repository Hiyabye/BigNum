#pragma once

#include "BigNum.h"

// Utility functions for BigNums
BigNum gcd(BigNum a, BigNum b);
BigNum lcm(BigNum &a, BigNum &b);
BigNum abs(const BigNum &bn);
BigNum pow(BigNum base, BigNum exp);