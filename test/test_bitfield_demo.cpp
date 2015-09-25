#include "tbitfield.h"

#include <gtest.h>

TEST(Demo, can_create_bitfield_with_size_1000)
{
    ASSERT_NO_THROW(TBitField bf(1000));
}

TEST(Demo, can_create_bitfield_with_size_minus_1000)
{
    ASSERT_ANY_THROW(TBitField bf(-1000));
}

TEST(Demo, can_set_bit_5)
{
    TBitField bf(10);
    EXPECT_EQ(0, bf.GetBit(5));

    bf.SetBit(5);
    EXPECT_NE(0, bf.GetBit(5));
}
