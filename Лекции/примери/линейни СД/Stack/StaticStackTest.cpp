#include "staticStack.hpp"
#include "gtest/gtest.h"
using fmi::sdp::StaticStack;

TEST(StaticStackTest, TestDefaultCtor)
{
    StaticStack stack;
    ASSERT_TRUE(stack.isEmpty());
}

TEST(StaticStackTest, TestIsEmpty)
{
    StaticStack stack;
    ASSERT_TRUE(stack.isEmpty());

    stack.push(1);
    ASSERT_FALSE(stack.isEmpty());

    stack.pop();
    ASSERT_TRUE(stack.isEmpty());
}

TEST(StaticStackTest, TestIsFull)
{
    StaticStack stack(3);
    EXPECT_TRUE(stack.isEmpty());
    ASSERT_FALSE(stack.isFull());

    stack.push(1);
    ASSERT_FALSE(stack.isFull());
    stack.push(2);
    ASSERT_FALSE(stack.isFull());
    stack.push(3);
    ASSERT_TRUE(stack.isFull());
}

TEST(StaticStackTest, TestPush)
{
    StaticStack stack(3);
    EXPECT_TRUE(stack.isEmpty());

    stack.push(1);
    ASSERT_FALSE(stack.isEmpty());

    stack.push(2);
    stack.push(3);

    ASSERT_THROW(stack.push(4), std::overflow_error);
}

TEST(StaticStackTest, TestPop)
{
    StaticStack stack(3);
    EXPECT_TRUE(stack.isEmpty());

    ASSERT_THROW(stack.pop(), std::underflow_error);

    stack.push(1);
    stack.push(2);
    stack.push(3);

    ASSERT_EQ(stack.pop(), 3);
    ASSERT_EQ(stack.pop(), 2);
    ASSERT_EQ(stack.pop(), 1);

    ASSERT_TRUE(stack.isEmpty());
    stack.push(4);
    ASSERT_EQ(stack.pop(), 4);

    ASSERT_THROW(stack.pop(), std::underflow_error);
}

TEST(StaticStackTest, TestTop)
{
    StaticStack stack(3);
    EXPECT_TRUE(stack.isEmpty());

    ASSERT_THROW(stack.top(), std::underflow_error);

    stack.push(1);
    stack.push(2);

    ASSERT_EQ(stack.top(), 2);
    ASSERT_EQ(stack.top(), 2);

    EXPECT_EQ(stack.pop(), 2);

    ASSERT_EQ(stack.top(), 1);
    stack.pop();

    ASSERT_THROW(stack.top(), std::underflow_error);
}

TEST(StaticStackTest, TestCopyCtor)
{
    StaticStack stack(3);
    EXPECT_TRUE(stack.isEmpty());
    stack.push(1);
    stack.push(2);
    stack.push(3);

    StaticStack copy(stack);
    ASSERT_FALSE(copy.isEmpty());

    while (!stack.isEmpty())
        ASSERT_EQ(stack.pop(), copy.pop());

    ASSERT_TRUE(copy.isEmpty());
}


TEST(StaticStackTest, TestAssignment)
{
    StaticStack stack(3);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    StaticStack copyBig;
    copyBig.push(100);
    copyBig.push(200);
    copyBig.push(300);
    copyBig.push(400);

    StaticStack copySmall(2);
    copySmall.push(50);
    ASSERT_THROW(copySmall = stack, std::overflow_error);
    ASSERT_TRUE(copySmall.pop() == 50);
    ASSERT_TRUE(copySmall.isEmpty());

    copyBig = stack;
    while (!stack.isEmpty())
        ASSERT_EQ(stack.pop(), copyBig.pop());

    ASSERT_TRUE(copyBig.isEmpty());
}
