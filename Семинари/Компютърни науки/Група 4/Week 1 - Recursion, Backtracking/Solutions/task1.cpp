#include <bits/stdc++.h>
using namespace std;

void nQueenUtil(int j, int n, vector<int> &board,
vector<vector<int>> &result, vector<bool> &rows,
vector<bool> &diag1, vector<bool> &diag2){
  if (j > n){
      
        result.push_back(board);
        return;
    }
    for (int i = 1; i <= n; ++i){
        if (!rows[i] && !diag1[i + j] &&
                          !diag2[i - j + n]){

            rows[i] = diag1[i + j] =
                        diag2[i - j + n] = true;
            board.push_back(i);

            nQueenUtil(j + 1, n, board, result,
                            rows, diag1, diag2);

            board.pop_back();
            rows[i] = diag1[i + j] =
                    diag2[i - j + n] = false;
        }
    }
}

vector<vector<int>> nQueen(int n){
    vector<vector<int>> result;
    vector<int> board;

    vector<bool> rows(n + 1, false);

    vector<bool> diag1(2 * n, false);

    vector<bool> diag2(2 * n, false);

    nQueenUtil(1, n, board, result, rows,
                                diag1, diag2);
    return result;
}

int main(){
    int n = 4;

    vector<vector<int>> result = nQueen(n);

    for (auto &res : result){
        cout << "[";
        for (int i = 0; i < n; ++i){
            cout << res[i];
            if (i != n - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}
