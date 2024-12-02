#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> nextGreaterElement(const vector<int> &nums)
{
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> s;

    for (int i = n - 1; i >= 0; --i)
    {
        while (!s.empty() && nums[i] >= nums[s.top()])
        {
            s.pop();
        }

        if (!s.empty())
        {
            result[i] = s.top();
        }

        s.push(i);
    }

    return result;
}

int main()
{
    vector<int> nums = {5, 3, 4, 7, 8, 1};
    vector<int> result = nextGreaterElement(nums);

    for (int index : result)
    {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}
