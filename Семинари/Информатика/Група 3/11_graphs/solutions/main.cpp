#include <iostream>
#include "Graph.hpp"

int main() {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(3, 8);
    g.addEdge(4, 2);
    g.addEdge(4, 6);
    g.addEdge(6, 8);
    g.addEdge(2, 1); // Remove this edge to make acyclic

    std::cout << "Dot:" << std::endl;
    g.printDot();

    std::cout << "BFS start 1:" << std::endl;
    auto bfs = g.bfsTraversal(1);
    for (int i: bfs) {
        std::cout << i << std::endl;
    }

    std::cout << "is cyclic:" << std::endl;
    std::cout << g.isCyclic() << std::endl;

    return 0;
}
