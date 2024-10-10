#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <climits>

class Solution {
public:
    bool find132pattern(vector<int> nums)
    {
        int s2 = INT_MIN;

        stack<int> stack;
        
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (nums[i] < s2) return true;
            
            while (!stack.empty() && nums[i] > stack.top())
            {
                s2 = stack.top();
                stack.pop();
            }

            stack.push(nums[i]);
        }

        return false;
    }

};