#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;

    bool operator<(const Edge &other) { return this->weight > other.weight; }
};

vector<Edge> edges;
int n, m;
int k;

int parent[1001];
int height[1001];

void initSet()
{
    for (int i = 1; i < n; ++i) {
        parent[i] = i;
        height[i] = 0;
    }
}

int findRoot(int v)
{
    if (v == parent[v]) {
        return v;
    }
    parent[v] = findRoot(parent[v]);
    return parent[v];
}

void unionSet(int u, int v)
{
    if (height[v] > height[u]) {
        std::swap(u, v);
    } else if (height[u] == height[v]) {
        ++height[u];
    }
    parent[v] = parent[u];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
    }
    cin >> k;

    sort(edges.begin(), edges.end());
    int res = 0;
    initSet();
    for (int i = 0; i < m; ++i) {
        int rootFrom = findRoot(edges[i].from);
        int rootTo = findRoot(edges[i].to);
        if (rootFrom != rootTo) {
            unionSet(rootFrom, rootTo);
            if (edges[i].weight < k) {
                res++;
            }
        }
    }

    cout << res << endl;
}