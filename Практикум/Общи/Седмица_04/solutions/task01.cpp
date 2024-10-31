#include <iostream>
#include <queue>


template <typename T>
std::queue<T> dropEverySecond(std::queue<T> q) {
    std::queue<T> result;
    bool skipNext = false;

    while (!q.empty()) {
        if (!skipNext) {
            result.push(q.front());
        }
        q.pop();
        skipNext = !skipNext;
    }

    return result;
}

int main () {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    auto filtered = dropEverySecond(q);

    while (!filtered.empty()) {
        std::cout << filtered.front() << ' ';
        filtered.pop();
    }
    std::cout << std::endl;

    return 0;
}
