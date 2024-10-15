#include <iostream>
#include <cstddef>
#include <iomanip>

const int MAX_MOVES = 8;
const int dX[] = { 1, 1, -1, -1, 2, -2, 2, -2 },
          dY[] = { 2, -2, 2, -2, 1, 1, -1, -1 };

/* helper functions(realization after main) */
template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal);
template <typename Type>
void deallocArr(Type* arr);
void print(int** matr, std::size_t size);

bool areValid(int i, int j, int n)
{
    return 0 <= i && i < n && 0 <= j && j < n;
}

bool hasPath(int curr, int i, int j, int n, int** chessBoard)
{
    chessBoard[i][j] = curr;
    if (curr == n * n - 1) return true;

    for (std::size_t k = 0; k < MAX_MOVES; ++k) {
        int x = i + dX[k], y = j + dY[k];

        if (areValid(x, y, n) && chessBoard[x][y] == -1 && hasPath(curr + 1, x, y, n, chessBoard)) {
            return true;
        }
    }
    chessBoard[i][j] = -1;
    return false;
}

int main()
{
    unsigned int n, startX, startY;
    std::cin >> n >> startX >> startY;

    int** chessBoard = allocArr<int*>(n, nullptr);
    for (std::size_t i = 0; i < n; ++i)
        chessBoard[i] = allocArr<int>(n, -1);

    if (hasPath(0, startX, startY, n, chessBoard) == false)
        std::cout << "The horse could not finish the tour\n";
    print(chessBoard, n);
    
    for (std::size_t i = 0; i < n; ++i)
        deallocArr<int>(chessBoard[i]);
    deallocArr<int*>(chessBoard);
    

    return 0;
}

template <typename Type>
Type* allocArr(std::size_t size, const Type& initVal)
{
    Type* arr = new Type[size];
    /* We do not handle the case where new fails
       cause this is not the focus of the problem */
    for (std::size_t i = 0; i < size; ++i)
        arr[i] = initVal;

    return arr;
}
template <typename Type>
void deallocArr(Type* arr)
{
    delete[] arr;
}
void print(int** matr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size - 1; ++j)
            std::cout << std::setw(3) << matr[i][j] << ' ';
        std::cout << std::setw(3) << matr[i][size - 1] << '\n';
    }
}