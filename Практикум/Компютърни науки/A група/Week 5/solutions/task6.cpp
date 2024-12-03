#include <iostream>
#include <vector>
#include <queue>

using std::vector;
#define boolMatrix vector<vector<bool>>

struct Coordinate
{
    size_t x, y;
    bool operator==(Coordinate other) { return x == other.x && y == other.y; };
};

struct Direction
{
    int x, y;
} directions[4]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

enum direction
{
    Down,
    Up,
    Right,
    Left
};

Coordinate getRollingCoordinate(boolMatrix grid, size_t N, size_t M, Coordinate curr, direction dir)
{
    int nextX = curr.x + directions[dir].x,
        nextY = curr.y + directions[dir].y;

    while (nextX >= 0 && nextX < N && nextY >= 0 && nextY < M && grid[nextX][nextY] == 0)
    {
        curr.x = nextX;
        curr.y = nextY;
        nextX = curr.x + directions[dir].x;
        nextY = curr.y + directions[dir].y;
    }
    return curr;
}

bool canReachEnd(boolMatrix &grid, size_t N, size_t M, Coordinate start, Coordinate end)
{
    std::queue<Coordinate> q;
    boolMatrix used(N, vector<bool>(M, false));

    q.push(start);
    Coordinate next, curr;
    used[start.x][start.y] = true;
    // BFS
    while (!q.empty())
    {
        curr = q.front();
        q.pop();

        if (curr == end)
            return true;

        for (int i = 0; i < 4; i++)
        {
            next = getRollingCoordinate(grid, N, M, curr, (direction)i);
            if (!used[next.x][next.y])
            {
                used[next.x][next.y] = 1;
                q.push(next);
            }
        }
    }
    return false;
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
    Coordinate start, end;
    std::cin >> start.x >> start.y >> end.x >> end.y;
    std::cout << canReachEnd(grid, N, M, start, end);
}

/*
5 5
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0
0 4
4 4


5 5
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0
0 4
3 2
*/