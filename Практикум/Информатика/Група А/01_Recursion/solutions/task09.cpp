class Solution {
public:
  vector<string> result;
  vector<string> restoreIpAddresses(string s) {
    dfs(s, 0, 0, "");
    return result;
  }
  bool isValid(const string &str) {
    if (str.size() == 0 || str.size() > 3) {
      return false;
    }
    if (str[0] == '0') {
      return str.size() == 1;
    }
    return std::stoi(str) > 0 && std::stoi(str) <= 255;
  }

  void dfs(const string &str, size_t startPos, int stepNumber,
           string currentResult) {
    if (startPos == str.size() && stepNumber == 4) {
      result.push_back(currentResult);
      return;
    }
    // Try putting a dot
    for (int i = 1; i < 4; ++i) {
      if (startPos + i > str.length()) {
        break;
      }
      string segment = str.substr(startPos, i);
      if (!isValid(segment)) {
        continue;
      }
      string candidate = currentResult + segment + (stepNumber == 3 ? "" : ".");
      dfs(str, startPos + i, stepNumber + 1, candidate);
    }
  }
};
