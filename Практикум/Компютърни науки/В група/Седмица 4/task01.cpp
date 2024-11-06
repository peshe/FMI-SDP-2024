#include <iostream>
#include <queue>
#include <string>

void printFirstKBinary(const int n)
{
    std::queue<std::string> q;
    q.push("1");

    int temp = 1;
    do {
        std::string curr = q.front();
        q.pop();

        std::cout << curr << std::endl;
        q.push(curr + '0');
        q.push(curr + '1');

        ++temp;
    } while (temp <= n);

    return;
}

int main()
{
    unsigned int n;
    std::cin >> n;

    printFirstKBinary(n);

    return 0;
}