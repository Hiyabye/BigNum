#include "../src/BigNum.h"
#include <gtest/gtest.h>

TEST(BigNumTest, Trim) {
  BigNum num1("000000000000");
  EXPECT_EQ(num1.num, "0");

  BigNum num2("000000000001");
  EXPECT_EQ(num2.num, "1");

  BigNum num3("000000123456789");
  EXPECT_EQ(num3.num, "123456789");

  BigNum num4("123456789.000000");
  EXPECT_EQ(num4.num, "123456789");
}

TEST(BigNumTest, Padding) {
  BigNum num1("01"), num2("1000");
  num1.padding(num1.num, num2.num);
  EXPECT_EQ(num1.num, "0001");
  EXPECT_EQ(num2.num, "1000");

  BigNum num3("123456789"), num4("987654321");
  num3.padding(num3.num, num4.num);
  EXPECT_EQ(num3.num, "123456789");
  EXPECT_EQ(num4.num, "987654321");

  BigNum num5("123456789"), num6("9876543210");
  num5.padding(num5.num, num6.num);
  EXPECT_EQ(num5.num, "0123456789");
  EXPECT_EQ(num6.num, "9876543210");
}

TEST(BigNumTest, Addition) {
  BigNum num1("123456789");
  BigNum num2("987654321");
  BigNum num3 = num1 + num2;
  EXPECT_EQ(num3.num, "1111111110");
}

TEST(BigNumTest, Subtraction) {
  BigNum num1("987654321");
  BigNum num2("123456789");
  BigNum num3 = num1 - num2;
  EXPECT_EQ(num3.num, "864197532");
}

TEST(BigNumTest, Multiplication) {
  BigNum num1("123456789");
  BigNum num2("987654321");
  BigNum num3 = num1 * num2;
  EXPECT_EQ(num3.num, "121932631112635269");
}

TEST(BigNumTest, Division) {
  BigNum num1("987654321"), num2("123456789");
  BigNum num3 = num1 / num2;
  EXPECT_EQ(num3.num, "8");

  BigNum num4("123456789"), num5("987654321");
  BigNum num6 = num4 / num5;
  EXPECT_EQ(num6.num, "0");

  BigNum num7("871264786124812"), num8("123456789");
  BigNum num9 = num7 / num8;
  EXPECT_EQ(num9.num, "7057244");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}