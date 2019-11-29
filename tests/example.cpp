//
// Created by waxta on 15.07.19.
//

#include "gtest/gtest.h"

int return1()
{
	return 1;
}

TEST(FirstTest, EqualsOne)
{
	EXPECT_EQ(2, return1());
}

TEST(SecondTest, EqualsThree)
{
	EXPECT_EQ(1, return1());
}