#include <iostream>
#include <unordered_map>
#include <vector>
#include "../Седмица 05 - Линеен едносвързан списък/linked_list.hpp"
#include "../Седмица 04 - Опашка/linked_queue.hpp"

// using Graph = std::unordered_map<int, std::vector<int>>;

template <typename K, typename V>
struct KeyValuePair {
  K key;
  V value;

  KeyValuePair(const K& key, const V& value) : key(key), value(value) {}
};

template <typename V>
class Graph {
public:
  using EdgeList = KeyValuePair<V, LinkedList<V>>;

  std::vector<V> vertices() const {
    std::vector<V> result;

    for (const EdgeList& el : data) {
      result.push_back(el.key);
    }

    return result;
  }

  LinkedList<V> successors(const V& u) const {
    for (const EdgeList& el : data) {
      if (el.key == u) {
        return el.value;
      }
    }

    return LinkedList<V>();
  }

  void add_vertex(const V& u) {
    data.push_back(EdgeList(u, LinkedList<V>()));
  }

  void add_edge(const V& u, const V& v) {
    for (EdgeList& el : data) {
      if (el.key == u) {
        el.value.insert_last(v);
      }
    }
  }

  void print() const {
    for (const EdgeList& el : data) {
      std::cout << el.key << " - ";
      for (const V& v : el.value) {
        std::cout << v << ' ';
      }
      std::cout << '\n';
    }
  }

private:
  std::vector<KeyValuePair<V, LinkedList<V>>> data;
};

template <typename C, typename T>
bool contains(const C& list, const T& element) {
  for (const T& data : list) {
    if (data == element) {
      return true;
    }
  }

  return false;
}

template <typename V>
std::pair<unsigned, unsigned> degree(const Graph<V>& graph, const V& u) {
  unsigned out_degree = graph.successors(u).get_size();
  unsigned in_degree = 0;

  for (int v : graph.vertices()) {
    if (contains(graph.successors(v), u)) {
      ++in_degree;
    }
  }

  return {in_degree, out_degree};
}

template <typename V>
Graph<V> invert(const Graph<V>& graph) {
  Graph<V> result;

  for (const V& v : graph.vertices()) {
    result.add_vertex(v);
  }

  for (const V& v : graph.vertices()) {
    for (const V& u : graph.successors(v)) {
      result.add_edge(u, v);
    }
  }

  return result;
}

template <typename V>
bool is_eulerian(const Graph<V>& graph) {
  for (const V& v : graph.vertices()) {
    std::pair<unsigned, unsigned> deg = degree(graph, v);

    if (deg.first % 2 != 0) {
      return false;
    }
  }

  return true;
}

template <typename V>
void dfs(const Graph<V>& graph, std::vector<V>& path, const V& v) {
  path.push_back(v);

  for (const V& u : graph.successors(v)) {
    if (!contains(path, u)) {
      dfs(graph, path, u);
    }
  }
}

template <typename V>
std::vector<V> dfs(const Graph<V>& graph) {
  std::vector<V> path;

  for (const V& v : graph.vertices()) {
    if (!contains(path, v)) {
      dfs(graph, path, v);
    }
  }

  return path;
}

template <typename V>
std::vector<V> path_to(const Graph<V>& graph, const V& u, const V& v) {
  std::vector<V> path;
  LinkedQueue<V> queue;
  queue.enqueue(u);

  while (!queue.empty()) {
    V current = queue.dequeue();

    if (!contains(path, current)) {
      path.push_back(current);

      for (const V& w : graph.successors(current)) {
        if (w == v) {
          path.push_back(v);
          return path;
        }

        queue.enqueue(w);
      }
    }
  }

  return std::vector<V>();
} 

int main() {
  Graph<int> graph;
  graph.add_vertex(1);
  graph.add_vertex(2);
  graph.add_vertex(3);
  graph.add_vertex(4);
  graph.add_vertex(5);

  graph.add_edge(1, 2);
  graph.add_edge(1, 3);
  graph.add_edge(1, 4);

  graph.add_edge(2, 1);
  graph.add_edge(2, 3);
  graph.add_edge(2, 5);

  graph.add_edge(3, 1);
  graph.add_edge(3, 2);
  graph.add_edge(3, 4);
  graph.add_edge(3, 5);

  graph.add_edge(4, 1);
  graph.add_edge(4, 3);
  graph.add_edge(4, 5);

  graph.add_edge(5, 2);
  graph.add_edge(5, 3);
  graph.add_edge(5, 4);

  graph.print();
  std::cout << '\n';

  /*
  1 - 2 3 4 
  2 - 1 3 5 
  3 - 1 2 4 5 
  4 - 1 3 5 
  5 - 2 3 4 
  */

  Graph<int> oriented_graph;
  oriented_graph.add_vertex(1);
  oriented_graph.add_vertex(2);
  oriented_graph.add_vertex(3);
  oriented_graph.add_vertex(4);
  oriented_graph.add_vertex(5);

  oriented_graph.add_edge(1, 2);
  oriented_graph.add_edge(1, 3);
  oriented_graph.add_edge(1, 4);

  oriented_graph.add_edge(2, 3);
  oriented_graph.add_edge(2, 5);

  oriented_graph.add_edge(3, 4);
  oriented_graph.add_edge(3, 5);

  oriented_graph.add_edge(5, 2);
  oriented_graph.add_edge(5, 4);

  oriented_graph.print();

  /*
  1 - 2 3 4 
  2 - 3 5 
  3 - 4 5 
  4 - 
  5 - 2 4 
  */

  std::pair<unsigned, unsigned> d1 = degree(oriented_graph, 1);
  std::cout << d1.first << ' ' << d1.second << '\n'; // -> 0 3

  std::pair<unsigned, unsigned> d2 = degree(oriented_graph, 2);
  std::cout << d2.first << ' ' << d2.second << '\n'; // -> 2 2

  Graph<int> inverted_graph = invert(oriented_graph);
  std::cout << '\n';
  inverted_graph.print();

  /*
  1 - 
  2 - 1 5 
  3 - 1 2 
  4 - 1 3 5 
  5 - 2 3 
  */

  std::cout << std::boolalpha << is_eulerian(graph) << '\n'; // -> false
  graph.add_vertex(6);
  graph.add_edge(6, 1);
  graph.add_edge(6, 2);
  graph.add_edge(6, 4);
  graph.add_edge(6, 5);

  graph.add_edge(1, 6);
  graph.add_edge(2, 6);
  graph.add_edge(4, 6);
  graph.add_edge(5, 6);
  std::cout << std::boolalpha << is_eulerian(graph) << '\n'; // -> false

  for (int v : dfs(oriented_graph)) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
  // 1 2 3 4 5 

  for (int v : dfs(inverted_graph)) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
  // 1 2 5 3 4

  oriented_graph.add_edge(1, 1);

  for (int v : path_to(oriented_graph, 1, 1)) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
  return 0;
}