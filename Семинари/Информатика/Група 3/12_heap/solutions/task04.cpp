#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge {
    int to, weight;

    Edge(int to, int weight) : to(to), weight(weight) {}

    bool operator<(const Edge &other) const {
        return this->weight > other.weight;
    }
};

class Graph {
private:
    std::vector<std::vector<Edge>> adjList;

public:
    explicit Graph(int vertices);

    void addEdge(int from, int to, int weight);

    int sumOfMinimalSpanningTree(int startVertex) const;
};


Graph::Graph(int vertices) {
    adjList.resize(vertices);
}

void Graph::addEdge(int from, int to, int weight) {
    adjList[from].emplace_back(to, weight);
    adjList[to].emplace_back(from, weight); // Add edge in reverse direction
}

int Graph::sumOfMinimalSpanningTree(int startVertex) const {
    int sum = 0;
    std::vector<bool> includedMST(this->adjList.size(), false);
    std::priority_queue<Edge> pq;

    // Start from the first vertex
    includedMST[startVertex] = true;
    for (const Edge &e: adjList[startVertex]) {
        pq.push(e);
    }

    while (!pq.empty()) {
        Edge currentEdge = pq.top();
        pq.pop();

        if (includedMST[currentEdge.to]) {
            continue; // Skip if the vertex is already in MST
        }

        // Include the vertex in MST
        includedMST[currentEdge.to] = true;
        sum += currentEdge.weight;

        // Add all edges from this vertex to the priority queue
        for (const Edge &neighbor: adjList[currentEdge.to]) {
            if (!includedMST[neighbor.to]) {
                pq.push(neighbor);
            }
        }
    }

    return sum;
}

int main() {
    Graph g(7); 

    g.addEdge(0, 3, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(0, 1, 3);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 4, 3);

    g.addEdge(2, 3, 5);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 5, 6);

    g.addEdge(3, 5, 7);

    g.addEdge(4, 5, 8);

    g.addEdge(5, 6, 9);

    int startVertex = 0;
    std::cout << g.sumOfMinimalSpanningTree(startVertex) << std::endl;

    return 0;
}
