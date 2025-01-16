class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const auto& str : strs) {
            string sorted = str;
            sort(sorted.begin(), sorted.end());

            groups[sorted].push_back(str);
        }

        vector<vector<string>> result;
        for (const auto& group : groups) {
            const auto& groupMembers = group.second;

            result.push_back(groupMembers);
        }
        return result;
    }
};
