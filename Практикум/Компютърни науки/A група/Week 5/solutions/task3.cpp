#include <iostream>
#include <vector>
#include <queue>

using std::vector;
#define boolMatrix vector<vector<bool>>

struct Coordinate
{
    size_t x, y;
};

void DFS(int x, int y, size_t N, size_t M, boolMatrix &used, const boolMatrix &grid)
{
    if (x < 0 || x >= N)
        return;
    if (y < 0 || y >= M)
        return;
    if (used[x][y])
        return;
    if (!grid[x][y])
        return;

    used[x][y] = 1;

    DFS(x - 1, y, N, M, used, grid);
    DFS(x + 1, y, N, M, used, grid);
    DFS(x, y - 1, N, M, used, grid);
    DFS(x, y + 1, N, M, used, grid);
}

int countIslands(const boolMatrix &grid, size_t N, size_t M)
{
    boolMatrix used(N, vector<bool>(M, false));
    int islands = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (grid[i][j] && !used[i][j])
            {
                DFS(i, j, N, M, used, grid);
                islands++;
            }
        }
    }
    return islands;
}

int islandPerimeter(const boolMatrix &grid, size_t N, size_t M, size_t x, size_t y)
{
    if (!grid[x][y])
        return -1;

    // BFS
    std::queue<Coordinate> q;
    boolMatrix used(N, vector<bool>(M, false));
    size_t perimeter = 0, X, Y;

    q.push({x, y});
    used[x][y] = true;

    while (!q.empty())
    {
        X = q.front().x;
        Y = q.front().y;
        q.pop();

        perimeter += 4;

        if (X > 0 && grid[X - 1][Y])
        {
            if (!used[X - 1][Y])
            {
                q.push({X - 1, Y});
                used[X - 1][Y] = 1;
            }
            perimeter--;
        }
        if (X + 1 < N && grid[X + 1][Y])
        {
            if (!used[X + 1][Y])
            {
                q.push({X + 1, Y});
                used[X + 1][Y] = 1;
            }
            perimeter--;
        }
        if (Y > 0 && grid[X][Y - 1])
        {
            if (!used[X][Y - 1])
            {
                q.push({X, Y - 1});
                used[X][Y - 1] = 1;
            }
            perimeter--;
        }
        if (Y + 1 < M && grid[X][Y + 1])
        {
            if (!used[X][Y + 1])
            {
                q.push({X, Y + 1});
                used[X][Y + 1] = 1;
            }
            perimeter--;
        }
    }
    return perimeter;
}

int main()
{
    int N, M;
    bool b;

    std::cin >> N >> M;
    boolMatrix grid(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cin >> b;
            grid[i][j] = b;
        }
    }
    std::cout << countIslands(grid, N, M) << std::endl;
    std::cout << islandPerimeter(grid, N, M, 1, 1) << std::endl;
}

/*
4 4
0 1 0 0
1 1 1 0
0 0 0 0
1 1 0 0
*/