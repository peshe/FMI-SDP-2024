#include <string>
#include <stdexcept>

#include "staticQueue.hpp"
#include "gtest/gtest.h"

using fmi::sdp::StaticQueue;
using std::string;

TEST(StaticQueueTest, TestDefaultCtor)
{
    StaticQueue<char> queue;
    ASSERT_TRUE(queue.isEmpty());
}

TEST(StaticQueueTest, TestIsEmpty)
{
    StaticQueue<int> queue;
    ASSERT_TRUE(queue.isEmpty());

    queue.enqueue(1);
    ASSERT_FALSE(queue.isEmpty());

    queue.dequeue();
    ASSERT_TRUE(queue.isEmpty());
}

TEST(StaticQueueTest, TestIsFull)
{
    StaticQueue<int> queue(3);
    EXPECT_TRUE(queue.isEmpty());
    ASSERT_FALSE(queue.isFull());

    queue.enqueue(1);
    ASSERT_FALSE(queue.isFull());
    queue.enqueue(2);
    ASSERT_FALSE(queue.isFull());
    queue.enqueue(3);
    ASSERT_TRUE(queue.isFull());
}

TEST(StaticQueueTest, TestEnqueue)
{
    StaticQueue<int> queue(3);
    EXPECT_TRUE(queue.isEmpty());

    queue.enqueue(1);
    ASSERT_FALSE(queue.isEmpty());

    queue.enqueue(2);
    queue.enqueue(3);

    ASSERT_THROW(queue.enqueue(4), std::overflow_error);
}

TEST(StaticQueueTest, TestDequeue)
{
    StaticQueue<string> queue(3);
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

TEST(StaticQueueTest, TestFirst)
{
    StaticQueue<int> queue(3);
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

TEST(StaticQueueTest, TestCopyCtor)
{
    StaticQueue<int> queue(3);
    EXPECT_TRUE(queue.isEmpty());
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    StaticQueue<int> copy(queue);
    ASSERT_FALSE(queue.isEmpty());

    while (!queue.isEmpty())
        ASSERT_EQ(queue.dequeue(), copy.dequeue());

    ASSERT_TRUE(copy.isEmpty());
}


TEST(StaticQueueTest, TestAssignment)
{
    StaticQueue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    StaticQueue<int> copyBig;
    copyBig.enqueue(100);
    copyBig.enqueue(200);
    copyBig.enqueue(300);
    copyBig.enqueue(400);

    StaticQueue<int> copySmall(2);
    copySmall.enqueue(50);
    ASSERT_THROW(copySmall = queue, std::overflow_error);

    copyBig = queue;
    while (!queue.isEmpty())
        ASSERT_EQ(queue.dequeue(), copyBig.dequeue());

    ASSERT_TRUE(copyBig.isEmpty());
}
