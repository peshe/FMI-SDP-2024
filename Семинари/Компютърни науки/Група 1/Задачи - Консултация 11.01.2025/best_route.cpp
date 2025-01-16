#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
	int to;
	int w;
};

std::vector<int> dist(std::vector<std::vector<Edge>> &g, int start) {
	std::vector<int> dist(g.size(), INT_MAX);

	std::queue<int> q;
	q.push(start);
	dist[start] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (Edge ed : g[v]) {
			if (ed.w + dist[v] < dist[ed.to]) {
				dist[ed.to] = ed.w + dist[v];
				q.push(ed.to);
			}
		}
	}

	return dist;
};

int main() {
	std::vector<std::vector<Edge>> g;

	int N, M;
	std::cin >> N >> M;
	g.resize(N);
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		g[a].push_back({b, c});
	}

	std::vector<int> d = dist(g, 0);

	for(int dist : d) std::cout << dist << std::endl;
}
