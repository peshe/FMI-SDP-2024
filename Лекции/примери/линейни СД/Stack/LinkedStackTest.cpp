#include "linkedStack.hpp"
#include "gtest/gtest.h"

using fmi::sdp::LinkedStack;

TEST(LinkedStackTest, TestDefaultCtor)
{
    LinkedStack<int> stack;
    ASSERT_TRUE(stack.isEmpty());
}

TEST(LinkedStackTest, TestIsEmpty)
{
    LinkedStack<int> stack;
    ASSERT_TRUE(stack.isEmpty());

    stack.push(1);
    ASSERT_FALSE(stack.isEmpty());

    stack.pop();
    ASSERT_TRUE(stack.isEmpty());
}

TEST(LinkedStackTest, TestPush)
{
    LinkedStack<int> stack;
    EXPECT_TRUE(stack.isEmpty());

    stack.push(1);
    ASSERT_FALSE(stack.isEmpty());
    ASSERT_EQ(stack.top(), 1);

    stack.push(2);
    ASSERT_EQ(stack.top(), 2);

    stack.push(3);
    ASSERT_EQ(stack.top(), 3);
}

TEST(LinkedStackTest, TestPop)
{
    LinkedStack<int> stack;
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

TEST(LinkedStackTest, TestTop)
{
    LinkedStack<int> stack;
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

TEST(LinkedStackTest, TestCopyCtor)
{
    LinkedStack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    stack.push(1);
    stack.push(2);
    stack.push(3);

    LinkedStack<int> copy(stack);
    ASSERT_FALSE(copy.isEmpty());

    while (!stack.isEmpty())
        ASSERT_EQ(stack.pop(), copy.pop());

    ASSERT_TRUE(copy.isEmpty());
}


TEST(LinkedStackTest, TestAssignment)
{
    LinkedStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    LinkedStack<int> copy;
    copy.push(100);
    copy.push(200);
    copy.push(300);
    copy.push(400);

    copy = stack;
    while (!stack.isEmpty())
        ASSERT_EQ(stack.pop(), copy.pop());

    ASSERT_TRUE(copy.isEmpty());
}
