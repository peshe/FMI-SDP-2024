#include <iostream>
#include <memory>
#include "graph.hpp"

int main() {
	
	std::unique_ptr<Graph> g = std::make_unique<EdgeGraph>(10);
	g->addEdge({1,2});
	g->addEdge({2,3});
	g->addEdge({3,4});
	g->addEdge({4,1});
	g->addEdge({4,5});
	g->addEdge({5,6});
	
	std::cout << "neighbours of 4" << std::endl;
	g->forNeighbours(4, [](const Graph::Vertex &v) { std::cout << v << " "; });
	std::cout << std::endl;

	std::cout << "dfs from 4" << std::endl;
	g->dfs(4, [](Graph::Vertex &v) { std::cout << v << " "; });
	std::cout << std::endl;

	std::cout << "bfs from 4" << std::endl;
	g->bfs(4, [](Graph::Vertex &v) { std::cout << v << " "; });
	std::cout << std::endl;

	return 0;
}
