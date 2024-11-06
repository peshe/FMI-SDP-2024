#include <iostream>
#include <stack>
#include <queue>

bool couldBeSorted(std::queue<int>& q)
{
    int maxN = q.size();
    int currExpected = 1;
    std::stack<int> st;

    while (!q.empty())
    {
        int front = q.front();
        q.pop();

        if (front == currExpected) ++currExpected;
        else
        {
            if (st.empty())
                st.push(front);
            else if (!st.empty() && st.top() < front)
                return false;
            else st.push(front);
        }

        while (!st.empty() && st.top() == currExpected) {
            st.pop();
            currExpected++;
        }
    }

    return st.empty() && q.empty() && currExpected == maxN + 1;
}

int main()
{
    std::queue<int> q;
    q.push(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    std::cout << couldBeSorted(q) << std::endl;
    return 0;
}