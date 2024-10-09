#include <iostream>
#include <vector>

void printBoard(const std::vector<std::vector<bool>> &board) {
    for (std::size_t i = 0; i < board.size(); ++i) {
        for (std::size_t j = 0; j < board.size(); ++j) {
            std::cout << (board[i][j] ? "Q" : ". ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isSafe(const std::vector<std::vector<bool>> &board, std::size_t row,
            std::size_t col) {
    for (std::size_t i = 0; i < col; ++i) {
        if (board[row][i]) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    for (int i = row, j = col; i < board.size() && j >= 0; ++i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solveNQueensDFS(std::vector<std::vector<bool>> &board, std::size_t col, int n) {
    if (n == 0) {
        printBoard(board);
        return true;
    }

    for (std::size_t i = 0; i < board.size(); ++i) {
        if (isSafe(board, i, col)) {
            board[i][col] = true;
            if (solveNQueensDFS(board, col + 1, n - 1)) {
                return true;
            }
            board[i][col] = false;
        }
    }
    return false;
}

void solveNQueens(int n) {
    std::vector<std::vector<bool>> board(n, std::vector<bool>(n, false));

    if (!solveNQueensDFS(board, 0, n)) {
        std::cout << "No solution!\n";
    }
}

int main() {
    solveNQueens(20);
    return 0;
}
