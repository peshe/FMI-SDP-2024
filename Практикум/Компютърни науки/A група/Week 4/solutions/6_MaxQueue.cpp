#include <iostream>
#include <queue>
#include <stdexcept>

class MaxQueue
{
private:
    std::queue<int> mainQueue;
    std::deque<int> maxQueue;

public:
    void enqueue(int value)
    {
        mainQueue.push(value);
        while (!maxQueue.empty() && maxQueue.back() < value)
        {
            maxQueue.pop_back();
        }
        maxQueue.push_back(value);
    }

    void dequeue()
    {
        if (mainQueue.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        int removedValue = mainQueue.front();
        mainQueue.pop();
        if (removedValue == maxQueue.front())
        {
            maxQueue.pop_front();
        }
    }

    int getMax()
    {
        if (maxQueue.empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return maxQueue.front();
    }
};

int main()
{
    MaxQueue mq;

    mq.enqueue(3);
    mq.enqueue(2);
    mq.enqueue(1);
    mq.enqueue(7);
    mq.enqueue(3);

    std::cout << mq.getMax() << std::endl;
    mq.dequeue();
    mq.dequeue();
    std::cout << mq.getMax() << std::endl;
    mq.dequeue();
    std::cout << mq.getMax() << std::endl;
    mq.dequeue();
    std::cout << mq.getMax() << std::endl;
    mq.dequeue();

    return 0;
}
