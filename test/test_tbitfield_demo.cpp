#include "tbitfield.h"

#include <gtest.h>

TEST(TBitField_Demo, can_create_bitfield_with_positive_length)
{
    ASSERT_NO_THROW(TBitField bf(1));
}

TEST(TBitField_Demo, cant_create_bitfield_with_negative_length)
{
    ASSERT_ANY_THROW(TBitField bf(-1));
}

TEST(TBitField_Demo, cant_create_bitfield_with_zero_length)
{
    ASSERT_ANY_THROW(TBitField bf(0));
}

TEST(TBitField_Demo, can_get_length)
{
    TBitField bf(10);

    EXPECT_EQ(10, bf.GetLength());
}

// A new one of these is created for each test
class TBitField_Demo_Fixture : public testing::Test
{
public:
  TBitField bf_;

  TBitField_Demo_Fixture() : bf_(10) {}

  virtual void SetUp()
  {
      for (int i = 1; i < bf_.GetLength(); i += 2)
      {
          bf_.SetBit(i);
      }
  }

  virtual void TearDown() {}
};

TEST_F(TBitField_Demo_Fixture, can_get_length)
{
    EXPECT_EQ(10, bf_.GetLength());
}

TEST_F(TBitField_Demo_Fixture, all_even_bits_are_set)
{
    for (int i = 1; i < bf_.GetLength(); i += 2)
    {
        EXPECT_NE(0, bf_.GetBit(i));
    }
}

TEST_F(TBitField_Demo_Fixture, all_odd_bits_are_unset)
{
    for (int i = 0; i < bf_.GetLength(); i += 2)
    {
        EXPECT_EQ(0, bf_.GetBit(i));
    }
}

class Parameterized_TBitField_Demo : public ::testing::TestWithParam<int> {
  // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
};

TEST_P(Parameterized_TBitField_Demo, can_create_bitfield_with_different_len)
{
    int len = GetParam();

    TBitField bf(len);

    EXPECT_EQ(len, bf.GetLength());
}

TEST_P(Parameterized_TBitField_Demo, can_set_different_bits)
{
    TBitField bf(100);

    int idx = GetParam();
    EXPECT_EQ(0, bf.GetBit(idx));

    bf.SetBit(idx);
    EXPECT_NE(0, bf.GetBit(idx));
}

INSTANTIATE_TEST_CASE_P(Even,
                        Parameterized_TBitField_Demo,
                        ::testing::Values(2, 4, 8));

INSTANTIATE_TEST_CASE_P(Odd,
                        Parameterized_TBitField_Demo,
                        ::testing::Values(3, 7, 13));
