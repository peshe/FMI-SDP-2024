#include <iostream>
#include <climits>

int N, M;

int minDistance[255][255];

void floyd()
{
    for(int k = 0; k < N; k++)
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(minDistance[i][k] != INT_MAX && minDistance[k][j] != INT_MAX)
                {
                    minDistance[i][j] = std::min(minDistance[i][j], minDistance[i][k] + minDistance[k][j]);
                }
            }
        }
    }
}


int main()
{
    std::cin >> N >> M;
    int a, b, c;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            minDistance[i][j] = INT_MAX;
        }
        minDistance[i][i] = 0;
    }
    for(int i = 0; i < M; i++)
    {
        std::cin >> a >> b >> c;
        minDistance[a][b] = c;
        minDistance[b][a] = c;
    }
    floyd();

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cout << minDistance[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
}

/*
    5 5
    0 1 1
    1 2 2
    1 4 4
    2 3 3
    2 4 1
*/
