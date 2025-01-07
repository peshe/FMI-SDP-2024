#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>

template <typename K, typename V = K>
class BinaryHeap {
public:
  using Comparator = std::function<bool(const K&, const K&)>;

  BinaryHeap(const Comparator& comparator) : comparator(comparator) {}

  BinaryHeap(const std::vector<K>& data, const Comparator& comparator) 
    : comparator(comparator) {
    for (const K& key : data) {
      this->data.push_back({key, key});
    }

    for (int i = data.size() / 2 - 1; i >= 0; --i) {
      heapify_down(i);
    }
  }

  bool empty() const {
    return data.empty();
  }

  std::size_t size() const {
    return data.size();
  }

  void insert(const K& key, const V& value) {
    data.push_back({key, value});
    heapify_up(data.size() - 1);
  }

  void insert(const K& key) {
    data.push_back({key, key});
    heapify_up(data.size() - 1);
  }

  const V& top() const {
    return data[0].value;
  }

  V pop() {
    V result = top();
    data[0] = data.back();
    data.pop_back();

    heapify_down(0);

    return result;
  }

  void update_key(std::size_t index, const K& new_key) {
    K old_key = data[index].key;
    data[index].key = new_key;

    if (comparator(old_key, new_key)) {
      heapify_down(index);
    } else {
      heapify_up(index);
    }
  }

  void merge(const BinaryHeap& other) {
    for (const KeyValuePair& pair : other.data) {
      data.push_back(pair);
    }

    for (int i = data.size() / 2 - 1; i >= 0; --i) {
      heapify_down(i);
    }
  }

private:
  struct KeyValuePair {
    K key;
    V value;
  };

  std::vector<KeyValuePair> data;
  Comparator comparator;

  std::size_t left(std::size_t index) const {
    return 2 * index + 1;
  }

  std::size_t right(std::size_t index) const {
    return 2 * index + 2;
  }

  int parent(int index) const {
    return (index - 1) / 2;
  }

  void heapify_up(int index) {
    int parent_index = parent(index);
    while (index > 0 && comparator(data[index].key, data[parent_index].key)) {
      std::swap(data[index], data[parent_index]);
      index = parent_index;
      parent_index = parent(index);
    }
  }

  void heapify_down(std::size_t index) {
    std::size_t smallest = index;
    std::size_t left_child = left(index);
    std::size_t right_child = right(index);

    if (left_child < data.size() && comparator(data[left_child].key, data[smallest].key)) {
      smallest = left_child;
    }

    if (right_child < data.size() && comparator(data[right_child].key, data[smallest].key)) {
      smallest = right_child;
    }

    if (smallest == index) {
      return;
    }

    std::swap(data[smallest], data[index]);
    heapify_down(smallest);
  }
};

template <typename T>
T find_kth_element(const std::vector<T>& arr, std::size_t k) {
  BinaryHeap<T> heap(arr, std::less<T>{});

  for (std::size_t i = 0; i < k - 1; ++i) {
    heap.pop();
  }

  return heap.top();
}

std::vector<double> medians(const std::vector<double>& arr) {
  BinaryHeap<double> max_heap(std::greater<double>{});
  BinaryHeap<double> min_heap(std::less<double>{});
  std::vector<double> result;

  for (double n : arr) {
    if (max_heap.empty() || n < max_heap.top()) {
      max_heap.insert(n);
    } else {
      min_heap.insert(n);
    }

    if (max_heap.size() < min_heap.size()) {
      max_heap.insert(min_heap.pop());
    }

    if (max_heap.size() > min_heap.size() + 1) {
      min_heap.insert(max_heap.pop());
    }

    if (max_heap.size() > min_heap.size()) {
      result.push_back(max_heap.top());
    } else {
      double average = (max_heap.top() + min_heap.top()) / 2;
      result.push_back(average);
    }
  }

  return result;
}

int main() {
  std::vector<int> arr = {19, 1, 17, 100, 2, 7, 3, 36, 25};

  BinaryHeap<int> heap(std::less<int>{});
  BinaryHeap<int> heap2({21, 10, 98}, std::less<int>{});

  for (int n : arr) {
    heap.insert(n);
  }

  heap.merge(heap2);
  // heap.update_key(0, -5);

  while (!heap.empty()) {
    std::cout << heap.pop() << ' ';
  }
  std::cout << '\n';

  std::cout << find_kth_element(arr, 4) << '\n'; // -> 7

  for (double n : medians({19, 1, 17, 100, 2, 7, 3, 36, 25})) {
    std::cout << n << ' ';
  }
  std::cout << '\n';

  // -> 19 10 17 18 17 12 7 12 17
  return 0;
}