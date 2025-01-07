class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        size_t nCities = isConnected.size();
        vector<bool> visited(nCities, false);
        int nProvinces = 0;
        
        for (int i = 0; i < nCities; ++i) {
            if (visited[i]) continue;

            ++nProvinces;
            queue<int> toVisit;
            toVisit.push(i);

            while (!toVisit.empty()) {
                int current = toVisit.front();
                toVisit.pop();

                if(!visited[current]) {
                    visited[current] = true;
                    for (int j = 0; j < nCities; ++j) {
                        if (isConnected[current][j]) {
                            toVisit.push(j);
                        }
                    }
                }
            }
        }

        return nProvinces;
    }
};
