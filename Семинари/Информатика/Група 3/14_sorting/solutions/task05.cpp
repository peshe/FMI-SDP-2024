class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        const int MAX_ELEMENT_SIZE = 1001;
        int elementCounts[MAX_ELEMENT_SIZE] = {0};

        for(std::size_t i = 0; i < arr1.size(); ++i)
        {
            elementCounts[arr1[i]]++;
        }

        arr1.clear();

        for(std::size_t i = 0; i < arr2.size(); ++i)
        {
            for(int cnt = 0; cnt < elementCounts[arr2[i]]; ++cnt)
            {
                arr1.push_back(arr2[i]);
            }
            elementCounts[arr2[i]] = 0;
        }

        for(std::size_t i = 0; i < MAX_ELEMENT_SIZE; ++i)
        {
            for(int cnt = 0; cnt < elementCounts[i]; ++cnt)
            {
                arr1.push_back(i);
            }
        }

        return arr1;
    }
};