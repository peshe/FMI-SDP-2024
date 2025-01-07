class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> nTrusts(n + 1, 0);
        vector<int> nTrustedBy(n + 1, 0);

        for (const auto& trusts : trust) {
            ++nTrusts[trusts[0]];
            ++nTrustedBy[trusts[1]];
        }

        int result = -1;
        for (int i = 1; i <= n; ++i) {
            if (nTrusts[i] == 0 && nTrustedBy[i] == n - 1) {
                if (result == -1) {
                    result = i;
                }
                else {
                    return -1;
                }
            }
        }

        return result;
    }
};
