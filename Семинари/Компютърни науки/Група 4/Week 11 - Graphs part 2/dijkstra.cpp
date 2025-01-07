#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#define PA std::pair<int,int>

int N, M;
std::vector<PA> gr[255];
int minPath[255];

void dijkstra(int start)
{
    std::fill(minPath, minPath + N, INT_MAX);
    minPath[start] = 0;
    bool used[255];
    std::fill(used, used + N, false);
    std::priority_queue<PA, std::vector<PA>, std::greater<PA> > qu;
    qu.push({0, start});
    while(!qu.empty())
    {
        int node = qu.top().second;
        qu.pop();
        if(!used[node])
        {
            used[node] = true;
            for(int i = 0; i < gr[node].size(); i++)
            {
                if(minPath[gr[node][i].first] > minPath[node] + gr[node][i].second)
                {
                    minPath[gr[node][i].first] = minPath[node] + gr[node][i].second;
                    qu.push({minPath[gr[node][i].first], gr[node][i].first});
                }
            }
        }
    }
}
int main()
{
    std::cin >> N >> M;
    int a, b, c;
    for(int i = 0; i < M; i++)
    {
        std::cin >> a >> b >> c;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
    }
    dijkstra(0);
    for(int i = 0; i < N; i++)
    {
        std::cout << minPath[i] << std::endl;
    }
}