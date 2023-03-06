#include <ac_fixed.h>
#include <gtest/gtest.h>

class AcFxiedTest : public ::testing::Test {
protected:
  void SetUp() override {
    m_int3 = 2;
  }
  ac_fixed<4, 3> m_int3;
};

TEST_F(AcFxiedTest, BasicTest)
{
    EXPECT_EQ(m_int3, 2.0);
}
