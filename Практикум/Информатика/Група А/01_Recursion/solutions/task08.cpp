class Solution {
public:
  bool exist(vector<vector<char>> &board, string word) {
    if (board.empty() || board[0].empty()) {
      return false;
    }

    vector<vector<bool>> visited(board.size(),
                                 vector<bool>(board[0].size(), false));

    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
        if (search(board, i, j, word, 0, visited)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  // Do a DFS
  bool search(vector<vector<char>> &board, size_t row, size_t col,
              const string &key, size_t keyProgress,
              vector<vector<bool>> &visited) {
    if (keyProgress == key.size()) {
      return true;
    }

    if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size() ||
        visited[row][col] || board[row][col] != key[keyProgress]) {
      return false;
    }

    visited[row][col] = true;
    bool found = search(board, row + 1, col, key, keyProgress + 1, visited) ||
                 search(board, row - 1, col, key, keyProgress + 1, visited) ||
                 search(board, row, col + 1, key, keyProgress + 1, visited) ||
                 search(board, row, col - 1, key, keyProgress + 1, visited);
    visited[row][col] = false;
    return found;
  }
};
