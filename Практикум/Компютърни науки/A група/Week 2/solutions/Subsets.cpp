#include <iostream>
#include <vector>

void Print(const std::vector<int> &nums)
{
    std::cout<<"{ ";
    for (int a : nums)
        std::cout << a << " ";
    std::cout<<"}\n";
}

void Subsets1(const std::vector<int> &nums, int index, std::vector<int> &res)
{
    Print(res);
    if (index >= nums.size())
        return;

    for (size_t i = index; i < nums.size(); i++)
    {
        res.push_back(nums[i]);
        Subsets1(nums, i + 1, res);
        res.pop_back();
    }
}
void Subsets2(const std::vector<int> &nums, int index, std::vector<int> &res)
{
    if (index >= nums.size())
        return Print(res);
    Subsets2(nums, index + 1, res);
    res.push_back(nums[index]);
    Subsets2(nums, index + 1, res);
    res.pop_back();
}

int main()
{

    std::vector<int> a{1, 2, 3}, b;
    Subsets1(a, 0, b);
}