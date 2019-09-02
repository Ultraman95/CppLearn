#include "gtest/gtest.h"

int Foo(int a, int b)
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}

int Abs(int x)
{
	return x > 0 ? x : -x;
}

TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
}

TEST(IsAbsTest, HandlerTrueReturn)
{
	ASSERT_FALSE(Abs(1) == 1) << "Abs(1)=1";  //ASSERT_TRUE期待结果是true,operator<<输出一些自定义的信息
	ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
	ASSERT_FALSE(Abs(-2) == -2);  //期待结果是false
	ASSERT_EQ(Abs(1), Abs(-1));
	ASSERT_NE(Abs(-1), 0);
	ASSERT_LT(Abs(-1), 2);
	ASSERT_GT(Abs(-1), 0);
	ASSERT_LE(Abs(-1), 2);
	ASSERT_GE(Abs(-1), 0);
}