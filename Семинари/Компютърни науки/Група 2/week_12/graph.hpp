#pragma once

#include <functional>
#include <queue>
#include <stack>

/**
 *
 * vertices are 0..N-1
 * edges are pairs of vertices
 *
 */
class Graph {
   protected:
	std::size_t V;
	std::size_t E;

   public:
	using Vertex = std::size_t;
	using Edge	 = std::pair<Vertex, Vertex>;

	virtual void forNeighbours(const Vertex &, std::function<void(Vertex &)>) = 0;
	virtual void addEdge(const Edge &)										  = 0;
	virtual ~Graph()														  = default;
	Graph(std::size_t V, std::size_t E) : V(V), E(E) {}

	void dfsRec(Vertex start, const std::function<void(Vertex &)> &f) {
		bool *visited = new bool[V]{0};
		dfsRecH(start, visited, f);
		delete[] visited;
	}

	void dfsRecH(Vertex v, bool *visited, const std::function<void(Vertex &)> &f) {
		visited[v] = true;
		f(v);
		forNeighbours(v, [&](Vertex &neigh) {
			if (!visited[neigh]) { dfsRecH(neigh, visited, f); }
		});
	}

	void bfs(Vertex start, const std::function<void(Vertex &)> &f) {
		bool *visited = new bool[V]{0};
		bfsH(start, visited, f);
		delete[] visited;
	}

	void bfsH(Vertex start, bool *visited, const std::function<void(Vertex &)> &f) {
		std::queue<Vertex> q;
		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			Vertex v = q.front();
			q.pop();
			f(v);
			forNeighbours(v, [&](Vertex &neigh) {
				if (!visited[neigh]) {
					visited[neigh] = true;
					q.push(neigh);
				}
			});
		}
	}

	void dfs(Vertex start, const std::function<void(Vertex &)> &f) {
		bool *visited = new bool[V]{0};
		dfsH(start, visited, f);
		delete[] visited;
	}

	void dfsH(Vertex start, bool *visited, const std::function<void(Vertex &)> &f) {
		std::stack<Vertex> q;
		q.push(start);
		visited[start] = true;
		while (!q.empty()) {
			Vertex v = q.top();
			q.pop();
			f(v);
			forNeighbours(v, [&](Vertex &neigh) {
				if (!visited[neigh]) {
					visited[neigh] = true;
					q.push(neigh);
				}
			});
		}
	}
};

/// undirected graph with adjacency matrix
class MatrixGraph : public Graph {
	bool **matrix;

   public:
	MatrixGraph(std::size_t V) : Graph(V, 0) {
		matrix	   = new bool *[V];
		bool *data = new bool[V * V]{0};
		for (std::size_t i = 0; i < V; ++i) {
			matrix[i] = data + i * V;
		}
	}
	~MatrixGraph() {
		delete[] matrix[0];
		delete[] matrix;
	}

	MatrixGraph(const MatrixGraph &other)			 = delete;
	MatrixGraph &operator=(const MatrixGraph &other) = delete;
	MatrixGraph(MatrixGraph &&other)				 = delete;
	MatrixGraph &operator=(MatrixGraph &&other)		 = delete;

	void forNeighbours(const Vertex &v, std::function<void(Vertex &)> f) override {
		for (std::size_t i = 0; i < V; ++i) {
			if (matrix[v][i]) { f(i); }
		}
	}

	void addEdge(const Edge &e) override {
		matrix[e.first][e.second] = true;
		matrix[e.second][e.first] = true;
	}
};
