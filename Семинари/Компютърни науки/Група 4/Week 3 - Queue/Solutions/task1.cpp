#include <queue>
#include <iostream>

bool isSorted(std::queue<int> qu)
{
    std::queue<int> tmp;
    if(qu.empty())
    {
        return true;
    }
    int old = qu.front();
    tmp.push(old);
    qu.pop();
    int direction = 0;
    bool result = true;
    while(!qu.empty())
    {
        if(qu.front() > old)
        {
            if(direction == 0)
            {
                direction = 1;
            }
            else if(direction == -1)
            {
                result = false;
            }
        }
        else if(qu.front() < old)
        {
            if(direction == 0)
            {
                direction = -1;
            }
            else if(direction == 1)
            {
                result = false;
            }
        }
        tmp.push(qu.front());
        old = qu.front();
        qu.pop();
    }
    while(!tmp.empty())
    {
        qu.push(tmp.front());
        tmp.pop();
    }
    return result;
}
int main()
{
    std::queue<int> q1;
    for(int i = 1; i < 6; i++)
    {
        q1.push(i);
    }
    std::queue<int>q2;
    for(int i = 5; i >=1; i--)
    {
        q2.push(i);
    }
    std::queue<int>q3;
    q3.push(1);
    q3.push(3);
    q3.push(2);
    std::cout << std::boolalpha << isSorted(q1) << " " << isSorted(q2) << " " << isSorted(q3);
    
}