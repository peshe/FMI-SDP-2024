#include <iostream>
#include <vector>
void Print(const std::vector<int>& nums){
    for(int a:nums)
        std::cout<<a<<" ";
    std::cout<<std::endl;
}

void SumsCombination(const std::vector<int>& nums, int goal, size_t index, std::vector<int>& res){
    if(goal == 0)return Print(res);
    if(goal < 0)return;
    for(size_t i=index;i<nums.size();i++){
        res.push_back(nums[i]);
        SumsCombination(nums,goal-nums[i],i,res);
        res.pop_back();
    }
}

int main(){
    std::vector<int> a{2,3,6,7}, b;
    SumsCombination(a,7,0,b);

}