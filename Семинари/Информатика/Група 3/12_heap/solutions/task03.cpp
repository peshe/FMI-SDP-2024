#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) : to(to), weight(weight) {}
};


class Graph {
private:
    std::vector<std::vector<Edge>> adjList;

public:
    explicit Graph(int vertices);

    void addEdge(int from, int to, int weight); // Function to add an edge to the graph
    std::vector<int> dijkstra(int startNode) const;
};

Graph::Graph(int vertices) {
    adjList.resize(vertices);
}

void Graph::addEdge(int from, int to, int weight) {
    adjList[from].emplace_back(to, weight);
}

std::vector<int> Graph::dijkstra(int startNode) const {
    std::vector<int> distances(this->adjList.size(), std::numeric_limits<int>::max());
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq; // Distance is first because std::pairs are compared lexicographically.

    distances[startNode] = 0;
    // pq.push(std::make_pair(0, startNode)); // push vs emplace
    pq.emplace(0, startNode);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge &edge: adjList[u]) {
            if (distances[u] + edge.weight < distances[edge.to]) {
                distances[edge.to] = distances[u] + edge.weight;
                pq.emplace(distances[edge.to], edge.to);
            }
        }
    }

    return distances;
}

int main() {
    Graph g(5);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(4, 3, 1);

    int startVertex = 0;
    std::vector<int> distances = g.dijkstra(startVertex);

    for (int i = 0; i < distances.size(); ++i) {
        std::cout << "Distance from " << startVertex << " to " << i << " = " << distances[i] << std::endl;
    }

    return 0;
}
