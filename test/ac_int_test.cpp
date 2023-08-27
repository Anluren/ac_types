#include <ac_int.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

class AcIntTest : public ::testing::Test {
protected:
  void SetUp() override {
    m_int3 = 2;
    m_int4 = 7;
    m_uint3 = 2;
    m_uint4 = 7;
  }
  ac_int<3, true> m_int3;
  ac_int<4, true> m_int4;
  ac_int<3, false> m_uint3;
  ac_int<4, false> m_uint4;
};

// Demonstrate some basic assertions.
TEST_F(AcIntTest, BasicTest) {
  EXPECT_EQ(m_int3, 2);
  EXPECT_EQ(m_uint3, 2);

  m_int3 = 0b111;
  m_uint3 = 0b111;
  EXPECT_EQ(m_int3, -1);
  EXPECT_EQ(m_uint3, 7);

  // singed int to unsigned conversion
  Ulong a;
  a = (Ulong)m_int3;
  EXPECT_EQ(a, std::numeric_limits<Ulong>::max());

  decltype(m_int3) temp;
  temp = m_int3;
  EXPECT_EQ(temp, -1);
  decltype(m_uint3) utemp;
  utemp = m_uint3;
  EXPECT_EQ(utemp, 7);

  EXPECT_EQ((m_int3 + m_int4), 6);

  auto plus_var = (m_int3 + m_int4);
  static_assert(decltype(plus_var)::width == 5, "");

  auto uplus_var = (m_int3 + m_int4);
  static_assert(decltype(uplus_var)::width == 5, "");
  EXPECT_EQ((m_uint3 + m_uint4), 14);

  auto mixed_plus_var = m_uint4 + m_int3;
  // unsigned integer is sign extended to be 5 bits, the addition will further extend 1 bit
  static_assert(decltype(mixed_plus_var)::width == 6, "");
  EXPECT_EQ(mixed_plus_var, 6);

  // left shift
  // Shift (result constrained by left operand)
  auto usll_var = m_uint4 << m_int3;
  static_assert(decltype(usll_var)::width == 4, "");
  EXPECT_EQ(m_uint4, 7);
  EXPECT_EQ(m_int3, -1);
  EXPECT_EQ(usll_var, 3);

  auto sll_var = m_int4 << m_uint3;
  static_assert(decltype(sll_var)::width == 4, "");
  std::cout << sll_var << std::endl;
  EXPECT_EQ(sll_var, 0);

}

TEST_F(AcIntTest, ArithTest) {
  ac_int<5> v5{31};
  EXPECT_EQ(v5, -1);
  ac_int<5> v5_1{31};
  EXPECT_EQ(v5_1, -1);

  // result bitwidth: 10
  auto mul_var = v5 * v5_1;
  static_assert(decltype(mul_var)::width == 10);
  EXPECT_EQ(mul_var, 1);

  v5 = -16;
  v5_1 = -15;
  mul_var = v5 * v5_1;
  EXPECT_EQ(mul_var, 240);

  ac_int<5, false> uv5 {31};
  auto mixed_mul_var = uv5 * v5;
  static_assert(decltype(mixed_mul_var)::width == 10);
  EXPECT_EQ(mixed_mul_var, -496);

  // static_assert(ac::nbits<5>::val == 3); 
  // static_assert(ac::nbits<127>::val == 7); 
  // std::cout<< (ac::nbits<5>::val) << std::endl;
  // std::cout<< (ac::nbits<8>::val) << std::endl;
  // std::cout<< (ac::nbits<256>::val) << std::endl;
}