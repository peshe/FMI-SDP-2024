class Solution {
public:
    void subsetXORUtil(vector<int>& nums, int idx, bool included, vector<int>&xors, int current)
    {
        if(idx == nums.size())
        {
            xors.push_back(current);
            return;
        }
        if(included)
        {
            subsetXORUtil(nums,idx+1,true,xors,current ^ nums[idx]);
            subsetXORUtil(nums,idx+1,false,xors,current ^ nums[idx]);
        }
        else
        {
            subsetXORUtil(nums,idx+1,true,xors,current);
            subsetXORUtil(nums,idx+1,false,xors,current);
        }
    }
    int subsetXORSum(vector<int>& nums) {
        vector<int>xors;
        subsetXORUtil(nums,0,true,xors,0);
        subsetXORUtil(nums,0,false,xors,0);
        int result = 0;
        for(int i = 0; i < xors.size(); i+=2)
        {
            std::cout << xors[i]<<std::endl;
            result += xors[i];
        }
        return result;
    }
};