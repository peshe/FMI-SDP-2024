#include "Graph.hpp"

void Graph::addVertex(int vertex) {
    if (!this->containsVertex(vertex))
        this->adjList[vertex] = std::vector<int>();
}

bool Graph::containsVertex(int vertex) const {
    return this->adjList.contains(vertex); // or .count(vertex) > 0
}

void Graph::addEdge(int from, int to) {
    this->addVertex(from);
    this->addVertex(to);

    if (!this->containsEdge(from, to))
        this->adjList[from].push_back(to);
}

bool Graph::containsEdge(int from, int to) const {
    if (!this->containsVertex(from) || !this->containsVertex(to)) {
        return false;
    }

    for (int vertex: adjList.at(from)) {
        if (vertex == to)
            return true;
    }

    return false;
}

std::vector<int> Graph::getAdjacent(int vertex) const {
    if (!this->containsVertex(vertex))
        return {};

    return this->adjList.at(vertex);
}

std::vector<int> Graph::getVertices() const {
    std::vector<int> result;

    for (std::pair<int, std::vector<int>> p: adjList) {
        result.push_back(p.first);
    }

    return result;
}

void Graph::printDot(std::ostream &out) const {
    out << "digraph G {" << std::endl;

    for (std::pair<int, std::vector<int>> p: adjList) {
        for (int v: p.second) {
            out << p.first << " -> " << v << std::endl;
        }
    }

    out << "}" << std::endl;
}

int Graph::numberOfParents(int vertex) const {
    int result = 0;
    if (!this->containsVertex(vertex)) {
        throw std::logic_error("Vertex doesn't exist in the graph!");
    }

    std::vector<int> vertices = this->getVertices();

    for (int u: vertices) {
        if (this->containsEdge(u, vertex)) {
            result++;
        }
    }

    return result;
}

bool Graph::isPath(const std::vector<int> &path) const {
    if (path.empty()) {
        return true;
    }
    if (path.size() == 1) {
        return this->containsVertex(path[0]);
    }

    // regular for or this thing:
    for (auto it = path.begin(); it != --path.end(); it++) {
        if (!this->containsEdge(*it, *(it + 1))) {
            return false;
        }
    }

    return true;
}

bool Graph::pathExists(int from, int to) const {
    std::set<int> visited;
    return this->pathExistsHelper(from, to, visited);
}

std::vector<int> Graph::bfsTraversal(int start) const {
    std::vector<int> result;
    std::set<int> visited;
    std::queue<int> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto neighbours = this->getAdjacent(current);
        for (int u: neighbours) {
            if (visited.count(u) == 0) {
                q.push(u);
                visited.insert(u);
            }
        }

        result.push_back(current);
    }

    return result;
}

bool Graph::pathExistsHelper(int from, int to, std::set<int> &visited) const {
    if (from == to) {
        return true;
    }

    visited.insert(from);
    std::vector<int> neighbours = this->getAdjacent(from);

    for (int v: neighbours) {
        if (visited.count(v) == 0 && this->pathExistsHelper(v, to, visited)) {
            return true;
        }
    }

    return false;
}

bool Graph::isCyclic() const {
    std::set<int> visited;
    std::vector<int> vertices = this->getVertices();

    for (int v: vertices) {
        std::set<int> currentPathVisited;
        currentPathVisited.insert(v);
        if (this->isCyclicHelper(v, visited, currentPathVisited)) {
            return true;
        }
    }

    return false;
}

bool Graph::isCyclicHelper(int start, std::set<int> &visited, std::set<int> &currentPathVisited) const {
    if (visited.count(start) == 0) {
        visited.insert(start);
        currentPathVisited.insert(start);

        std::vector<int> neighbours = this->getAdjacent(start);

        for (int v: neighbours) {
            if (visited.count(v) == 0 && isCyclicHelper(v, visited, currentPathVisited) ||
                currentPathVisited.count(v)) {
                return true;
            }
        }
    }
    currentPathVisited.erase(start);
    return false;
}

