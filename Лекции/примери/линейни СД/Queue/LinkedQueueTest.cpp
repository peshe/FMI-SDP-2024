#include <string>

#include "linkedQueue.hpp"
#include "gtest/gtest.h"

using fmi::sdp::LinkedQueue;
using std::string;

TEST(LinkedQueueTest, TestDefaultCtor)
{
    LinkedQueue<char> queue;
    ASSERT_TRUE(queue.isEmpty());
}

TEST(LinkedQueueTest, TestIsEmpty)
{
    LinkedQueue<int> queue;
    ASSERT_TRUE(queue.isEmpty());

    queue.enqueue(1);
    ASSERT_FALSE(queue.isEmpty());

    queue.dequeue();
    ASSERT_TRUE(queue.isEmpty());
}

TEST(LinkedQueueTest, TestIsFull)
{
    LinkedQueue<int> queue;
    EXPECT_TRUE(queue.isEmpty());
    ASSERT_FALSE(queue.isFull());
}

TEST(LinkedQueueTest, TestEnqueue)
{
    LinkedQueue<string> queue;
    EXPECT_TRUE(queue.isEmpty());

    queue.enqueue("1");
    ASSERT_FALSE(queue.isEmpty());

    queue.enqueue("2");
    queue.enqueue("3");

    ASSERT_FALSE(queue.isEmpty());
    ASSERT_FALSE(queue.isFull());
}

TEST(LinkedQueueTest, TestDequeue)
{
    LinkedQueue<string> queue;
    EXPECT_TRUE(queue.isEmpty());

    ASSERT_THROW(queue.dequeue(), std::underflow_error);

    queue.enqueue("1");
    queue.enqueue("2");
    queue.enqueue("3");

    ASSERT_EQ(queue.dequeue(), "1");
    ASSERT_EQ(queue.dequeue(), "2");
    ASSERT_EQ(queue.dequeue(), "3");

    queue.enqueue("1");
    queue.enqueue("2");
    ASSERT_EQ(queue.dequeue(), "1");
    queue.enqueue("3");
    ASSERT_EQ(queue.dequeue(), "2");
    ASSERT_EQ(queue.dequeue(), "3");

    ASSERT_TRUE(queue.isEmpty());
    queue.enqueue("4");
    ASSERT_EQ(queue.dequeue(), "4");

    ASSERT_THROW(queue.dequeue(), std::underflow_error);
}

TEST(LinkedQueueTest, TestFirst)
{
    LinkedQueue<int> queue;
    EXPECT_TRUE(queue.isEmpty());

    ASSERT_THROW(queue.first(), std::underflow_error);

    queue.enqueue(1);
    queue.enqueue(2);

    ASSERT_EQ(queue.first(), 1);
    ASSERT_EQ(queue.first(), 1);

    EXPECT_EQ(queue.dequeue(), 1);

    ASSERT_EQ(queue.first(), 2);
    queue.dequeue();

    ASSERT_THROW(queue.first(), std::underflow_error);
}

TEST(LinkedQueueTest, TestCopyCtor)
{
    LinkedQueue<int> queue;
    EXPECT_TRUE(queue.isEmpty());
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    LinkedQueue<int> copy(queue);
    ASSERT_FALSE(queue.isEmpty());

    while (!queue.isEmpty())
        ASSERT_EQ(queue.dequeue(), copy.dequeue());

    ASSERT_TRUE(copy.isEmpty());
}


TEST(LinkedQueueTest, TestAssignment)
{
    LinkedQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    LinkedQueue<int> copy;
    copy.enqueue(100);
    copy.enqueue(200);
    copy.enqueue(300);
    copy.enqueue(400);

    copy = queue;
    while (!queue.isEmpty())
        ASSERT_EQ(queue.dequeue(), copy.dequeue());

    ASSERT_TRUE(copy.isEmpty());
}
