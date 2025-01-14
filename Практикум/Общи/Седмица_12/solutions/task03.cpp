#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using Pair = std::pair<long long, int>;

struct Edge
{
    int to;
    int weight;
    int g;
    int r;
};

const long long int INF = 1e16;
const int SOURCE = 1;

int n, m;
long long s;
std::vector<Edge> graph[100001];
long long dist[100001];
bool visited[100001];

int main()
{
    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        int a, b, s, g, r;
        cin >> a >> b >> s >> g >> r;
        graph[a].push_back({b, s, g, r});
        graph[b].push_back({a, s, g, r});
    }

    std::fill(dist, dist + n + 1, INF);
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({s, SOURCE});

    while (!pq.empty()) {
        long long currentWeight = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode]) {
            continue;
        }
        visited[currentNode] = true;

        for (auto &[to, si, gi, ri] : graph[currentNode]) {
            long long waitTime = (currentWeight % (gi + ri));

            if (waitTime >= gi) {
                waitTime = gi + ri - waitTime;
            } else {
                waitTime = 0;
            }

            if (!visited[to] && currentWeight + si + waitTime < dist[to]) {
                dist[to] = currentWeight + si + waitTime;
                pq.push({dist[to], to});
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            cout << " ";
        }
        cout << dist[i];
    }
    cout << endl;

    return 0;
}
