#pragma once

#include <functional>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

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

	virtual void forNeighbours(const Vertex &, std::function<void(const Vertex &)>) = 0;
	virtual void addEdge(const Edge &)												= 0;
	virtual void removeEdge(const Edge &)											= 0;
	virtual bool checkEdge(const Edge &)											= 0;
	virtual ~Graph()																= default;
	Graph(std::size_t V, std::size_t E) : V(V), E(E) {}

	void dfsRec(Vertex start, const std::function<void(Vertex &)> &f) {
		bool *visited = new bool[V]{0};
		dfsRecH(start, visited, f);
		delete[] visited;
	}

	void dfsRecH(Vertex v, bool *visited, const std::function<void(Vertex &)> &f) {
		visited[v] = true;
		f(v);
		forNeighbours(v, [&](const Vertex &neigh) {
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
			forNeighbours(v, [&](const Vertex &neigh) {
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
			forNeighbours(v, [&](const Vertex &neigh) {
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

	void forNeighbours(const Vertex &v, std::function<void(const Vertex &)> f) override {
		for (std::size_t i = 0; i < V; ++i) {
			if (matrix[v][i]) { f(i); }
		}
	}
	void addEdge(const Edge &e) override {
		matrix[e.first][e.second] = true;
		matrix[e.second][e.first] = true;
	}
	void removeEdge(const Edge &e) override {
		matrix[e.first][e.second] = false;
		matrix[e.second][e.first] = false;
	}
	bool checkEdge(const Edge &e) override { return matrix[e.first][e.second]; }
};

class ListGraph : public Graph {
	std::vector<std::vector<Vertex>> g;

   public:
	ListGraph(std::size_t V) : Graph(V, 0) { g.resize(V); }

	ListGraph(const ListGraph &other)			 = delete;
	ListGraph &operator=(const ListGraph &other) = delete;
	ListGraph(ListGraph &&other)				 = delete;
	ListGraph &operator=(ListGraph &&other)		 = delete;

	void forNeighbours(const Vertex &v, std::function<void(const Vertex &)> f) override {
		for (const Vertex &u : g[v])
			f(u);
	}
	void addEdge(const Edge &e) override {
		g[e.first].push_back(e.second);
		g[e.second].push_back(e.first);
	}
	void removeEdge(const Edge &e) override {
		auto &[u, v] = e;
		for(size_t i = 0; i < g[u].size(); ++i) {
			if(g[u][i] == v) {
				std::swap(g[u][i], g[u].back());
				g[u].pop_back();
				break;
			}
		}
		for(size_t i = 0; i < g[v].size(); ++i) {
			if(g[v][i] == u) {
				std::swap(g[v][i], g[v].back());
				g[v].pop_back();
				break;
			}
		}
	}

	bool checkEdge(const Edge &e) override {
		auto &[u, v] = e;
		auto it = std::find(g[u].begin(), g[u].end(), v);
		return it != g[u].end();
	}
};


class EdgeGraph : public Graph {
	std::vector<Edge> l;

   public:
	EdgeGraph(std::size_t V) : Graph(V, 0) {}

	EdgeGraph(const EdgeGraph &other)			 = delete;
	EdgeGraph &operator=(const EdgeGraph &other) = delete;
	EdgeGraph(EdgeGraph &&other)				 = delete;
	EdgeGraph &operator=(EdgeGraph &&other)		 = delete;

	void forNeighbours(const Vertex &v, std::function<void(const Vertex &)> f) override {
		for(auto &[u,w] : l) {
			if(u == v) f(w);
		}
	}
	void addEdge(const Edge &e) override {
		auto &[u,v] = e;
		l.push_back({u,v});
		l.push_back({v,u});
	}
	void removeEdge(const Edge &e) override {
		l.erase(std::find(l.begin(), l.end(), e));
	}

	bool checkEdge(const Edge &e) override {
		return std::find(l.begin(), l.end(), e) != l.end();
	}
};
