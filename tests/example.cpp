//
// Created by waxta on 15.07.19.
//

#include "test_Example.cpp"
#include "gtest/gtest.h"

TEST(FirstTest, EqualsOne)
{
	EXPECT_EQ(2, return1());
}

TEST(SecondTest, EqualsThree)
{
	EXPECT_EQ(1, return1());
}