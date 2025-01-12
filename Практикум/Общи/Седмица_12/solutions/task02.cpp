#include <iostream>
#include <queue>
#include <vector>

const int SIZE = 100001;
const int INF = 1e9;

using Pair = std::pair<int, int>;
struct Edge
{
    int to;
    int price;
    int time;
};

int n, m, k;
std::vector<Edge> graph[SIZE];

int distance[SIZE];
bool visited[SIZE];

void input()
{
    std::cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int from, to, price, time;
        std::cin >> from >> to >> price >> time;
        graph[from].push_back({to, price, time});
    }
}

// Use Dijkstra to check
bool reachable(int maxPrice)
{
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pQueue;
    std::fill(distance, distance + SIZE, INF);
    std::fill(visited, visited + SIZE, false); // It is important to reset the values
    distance[1] = 0;
    pQueue.push({0, 1});

    while (!pQueue.empty()) {
        int currentTime = pQueue.top().first;
        int currentNode = pQueue.top().second;
        visited[currentNode] = true;
        pQueue.pop();

        for (int i = 0; i < graph[currentNode].size(); ++i) {
            int to = graph[currentNode][i].to;
            int edgePrice = graph[currentNode][i].price;
            int edgeTime = graph[currentNode][i].time;

            if (!visited[to] && edgePrice <= maxPrice && currentTime + edgeTime < distance[to]) {
                distance[to] = currentTime + edgeTime;
                pQueue.push({distance[to], to});
            }
        }
    }
    return distance[n] <= k;
}

int main()
{
    input();
    int left = 0;
    int right = 1000000;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (reachable(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (right == 1000000) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << left << std::endl;
    }

    return 0;
}