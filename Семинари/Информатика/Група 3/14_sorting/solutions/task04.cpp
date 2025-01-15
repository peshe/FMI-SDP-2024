class Solution {
public:
    int heightChecker(vector<int>& heights) {
        const int MAX_COUNTS = 100;
        int counts[MAX_COUNTS] = {0};
        int misplaced = 0;

        for(std::size_t i = 0; i < heights.size(); ++i)
        {
            counts[heights[i] - 1]++;
        }

        std::size_t heightIndex = 0;
        for(std::size_t i = 0; i < MAX_COUNTS; ++i)
        {
            while(counts[i] > 0)
            {
                if(heights[heightIndex] != i + 1)
                {
                    misplaced++;
                }
                counts[i]--;
                heightIndex++;
            }
        }

        return misplaced;
    }
};