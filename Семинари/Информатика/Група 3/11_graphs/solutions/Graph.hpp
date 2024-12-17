#ifndef SDP_20241211_GRAPH_HPP
#define SDP_20241211_GRAPH_HPP

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <queue>

class Graph {
public:
    void addVertex(int vertex);

    void addEdge(int from, int to);

    std::vector<int> getAdjacent(int vertex) const;

    void printDot(std::ostream &out = std::cout) const;

    std::vector<int> getVertices() const;

    bool containsVertex(int vertex) const;

    bool containsEdge(int from, int to) const;

    int numberOfParents(int vertex) const;

    bool isPath(const std::vector<int> &path) const;

    bool pathExists(int from, int to) const;

    std::vector<int> bfsTraversal(int start) const;

    bool isCyclic() const;

private:

    bool pathExistsHelper(int from, int to, std::set<int> &visited) const;

    bool isCyclicHelper(int start, std::set<int> &visited, std::set<int> &currentPathVisited) const;

private:
    std::map<int, std::vector<int>> adjList;
};


#endif //SDP_20241211_GRAPH_HPP
