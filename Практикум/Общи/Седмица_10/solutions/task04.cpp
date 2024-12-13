class Solution {
public:
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        set<int> aliceSizeSet, bobSizeSet;
        int aliceTotal = 0, bobTotal = 0;

        for (int size : aliceSizes) {
            aliceSizeSet.insert(size);
            aliceTotal += size;
        }

        for (int size : bobSizes) {
            bobSizeSet.insert(size);
            bobTotal += size;
        }

        int halfBobExtra = (bobTotal - aliceTotal) / 2;
        for (int size : bobSizeSet) {
            int matchingSize = size - halfBobExtra;
            if (aliceSizeSet.count(matchingSize) > 0) {
                return {matchingSize, size};
            }
        }

        return {0, 0};
    }
};
