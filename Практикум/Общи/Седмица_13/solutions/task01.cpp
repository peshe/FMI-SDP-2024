class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, size_t> counts;

        for (int num : nums) {
            ++counts[num];
        }

        size_t longestSubsequence = 0;

        for (auto iter : counts) {
            int currentNum = iter.first;

            auto prev = counts.find(currentNum - 1);
            if (prev != counts.end()) {

                size_t currentCount = iter.second;
                size_t previousCount = prev->second;

                if (currentCount + previousCount > longestSubsequence) {
                    longestSubsequence = currentCount + previousCount;
                }
            }
        }

        return longestSubsequence;
    }
};
