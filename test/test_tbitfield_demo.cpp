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
