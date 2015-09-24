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
