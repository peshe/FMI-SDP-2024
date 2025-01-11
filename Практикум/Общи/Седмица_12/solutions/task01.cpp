#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using std::cout;
using std::greater;
using std::make_pair;
using std::numeric_limits;
using std::priority_queue;
using std::size_t;
using std::vector;

typedef std::pair<double, size_t> WeightedEdge;
typedef vector<WeightedEdge> NeighborsList;
typedef vector<NeighborsList> NeighborsGraph;


// Finds the shortest distances in `graph` from the vertex `source` to all vertices.
vector<double> dijkstra(const NeighborsGraph& graph, size_t source) {
    const size_t nVertices = graph.size();
    assert(0 <= source && source < nVertices);

    vector<bool> visited(nVertices, false);
    size_t nVisited = 0;
    vector<double> shortest(nVertices, numeric_limits<double>::max());

    priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge>> nextBest;
    shortest[source] = 0;
    nextBest.push(make_pair(0, source));

    while (!nextBest.empty()) {
        auto currentBest = nextBest.top();
        nextBest.pop();
        
        if (visited[currentBest.second]) continue;
        visited[currentBest.second] = true;
        if (++nVisited == nVertices) break;

        for (const auto& edge : graph[currentBest.second]) {
            if (visited[edge.second]) continue;

            double newRoute = currentBest.first + edge.first;
            if (newRoute < shortest[edge.second]) {
                shortest[edge.second] = newRoute;
                nextBest.push(make_pair(newRoute, edge.second));
            }
        }
    }

    return shortest;
}

// Finds the shortest path in `graph` from the vertex `source` to the vertex `destination`.
vector<size_t> dijkstra(const NeighborsGraph& graph, size_t source, size_t destination) {
    const size_t nVertices = graph.size();
    assert(0 <= source && source < nVertices && 0 <= destination && destination < nVertices);

    vector<bool> visited(nVertices, false);
    vector<double> shortest(nVertices, numeric_limits<double>::max());

    constexpr size_t MAX_SIZE_T = numeric_limits<size_t>::max();
    vector<size_t> previous(nVertices, MAX_SIZE_T);

    priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge>> nextBest;
    shortest[source] = 0;
    nextBest.push(make_pair(0, source));

    while (!nextBest.empty()) {
        auto currentBest = nextBest.top();
        nextBest.pop();

        if (currentBest.second == destination) {
            return previous;
        }

        if (visited[currentBest.second]) continue;
        visited[currentBest.second] = true;

        for (const auto& edge : graph[currentBest.second]) {
            if (visited[edge.second]) continue;

            double newRoute = currentBest.first + edge.first;
            if (newRoute < shortest[edge.second]) {
                shortest[edge.second] = newRoute;
                nextBest.push(make_pair(newRoute, edge.second));
                previous[edge.second] = currentBest.second;
            }
        }
    }

    assert(false);
}

int main() {
    NeighborsGraph graph = {
        {},
        { make_pair(7, 2), make_pair(9, 3), make_pair(14, 6), },
        { make_pair(7, 1), make_pair(10, 3), make_pair(15, 4), },
        { make_pair(9, 1), make_pair(10, 2), make_pair(11, 4), make_pair(2, 6), },
        { make_pair(15, 2), make_pair(11, 3), make_pair(6, 5), },
        { make_pair(6, 4), make_pair(9, 6), },
        { make_pair(14, 1), make_pair(2, 3), make_pair(9, 5), },
    };

    constexpr size_t source = 1;
    auto shortest = dijkstra(graph, source);
    for (size_t i = 0; i < graph.size(); ++i) {
        cout << i << ": " << shortest[i] << '\n';
    }
    cout << std::endl;

    constexpr size_t destination = 5;
    auto prev = dijkstra(graph, source, destination);
    for (size_t i = destination; i != source; i = prev[i]) {
        cout << i << " <- " << prev[i] << " (";
        for (const auto& edge : graph[i]) {
            if (edge.second == prev[i]) {
                cout << edge.first << ")\n";
                break;
            }
        }
    }

    return 0;
}
