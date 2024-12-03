#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using std::vector;
#define intMatrix vector<vector<int>>
#define boolMatrix vector<vector<bool>>

struct Coordinate
{
    size_t x, y;
};

void calculateExits(intMatrix &grid, size_t N, size_t M)
{
    std::queue<Coordinate> q;
    boolMatrix used(N, vector<bool>(M, false));

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            if (grid[i][j] == 0)
            {
                q.push({i, j});
                used[i][j] = 1;
            }
            if (grid[i][j] == -1)
                used[i][j] = true;
        }
    }

    size_t X, Y, layerSize = q.size(), nextLayerSize = 0, depth = 0;
    // BFS
    while (!q.empty())
    {
        X = q.front().x;
        Y = q.front().y;
        q.pop();

        grid[X][Y] = depth;
        layerSize--;

        if (X > 0 && !used[X - 1][Y])
        {
            used[X - 1][Y] = true;
            nextLayerSize++;
            q.push({X - 1, Y});
        }
        if (Y > 0 && !used[X][Y - 1])
        {
            used[X][Y - 1] = true;
            nextLayerSize++;
            q.push({X, Y - 1});
        }
        if (X + 1 < N && !used[X + 1][Y])
        {
            used[X + 1][Y] = true;
            nextLayerSize++;
            q.push({X + 1, Y});
        }
        if (Y + 1 < M && !used[X][Y + 1])
        {
            used[X][Y + 1] = true;
            nextLayerSize++;
            q.push({X, Y + 1});
        }

        if (layerSize == 0)
        {
            layerSize = nextLayerSize;
            nextLayerSize = 0;
            depth++;
        }
    }
}
int main()
{
    size_t N, M;
    std::cin >> N >> M;
    intMatrix grid(N, vector<int>(M, false));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cin >> grid[i][j];
        }
    }
    calculateExits(grid, N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cout << std::setw(2) << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
