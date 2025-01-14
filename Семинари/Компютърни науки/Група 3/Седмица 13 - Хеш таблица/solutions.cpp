#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "../Седмица 05 - Линеен едносвързан списък/linked_list.hpp"
#include "../Седмица 06 - Други видове списъци/doubly_linked_list.hpp"

template <typename K, typename V>
struct KeyValuePair {
  K key;
  V value;

  KeyValuePair(const K& key, const V& value) : key(key), value(value) {}
};

template <typename K, typename V>
class Dictionary {
public:
  using Hash = std::function<unsigned(const K& key)>;
  using Bucket = LinkedList<KeyValuePair<K, V>>;

  Dictionary(const Hash& hash, std::size_t capacity = 128)
    : hash(hash), data(std::vector<Bucket>(capacity)) {}

  void set(const K& key, const V& value) {
    unsigned index = hash(key) % data.capacity();
    Bucket& bucket = data[index];
    typename Bucket::Iterator bucket_iterator = bucket_find(bucket, key);

    if (bucket_iterator != bucket.end()) {
      *bucket_iterator = {key, value};
      return;
    }

    bucket.insert_last({key, value});

    if (load_factor() > load_factor_threshold) {
      resize();
    }
  }

  std::optional<V> lookup(const K& key) const {
    unsigned index = hash(key) % data.capacity();
    const Bucket& bucket = data[index];
    typename Bucket::Iterator bucket_iterator = bucket_find(bucket, key);

    if (bucket_iterator == bucket.end()) {
      return std::nullopt;
    }

    return (*bucket_iterator).value;
  }

  void remove(const K& key) {
    unsigned index = hash(key) % data.capacity();
    Bucket& bucket = data[index];
    typename Bucket::Iterator bucket_iterator = bucket_find(bucket, key);

    if (bucket_iterator != bucket.end()) {
      bucket.remove_at(bucket_iterator);
    }
  }

  std::vector<K> keys() const {
    std::vector<K> result;

    for (const Bucket& bucket : data) {
      for (const KeyValuePair<K, V>& pair : bucket) {
        result.push_back(pair.key);
      }
    }

    return result;
  }

  std::vector<V> values() const {
    std::vector<V> result;

    for (const Bucket& bucket : data) {
      for (const KeyValuePair<K, V>& pair : bucket) {
        result.push_back(pair.value);
      }
    }

    return result;
  }

  class Iterator {
  public:
    Iterator(const Dictionary<K, V>* dict, typename Bucket::Iterator it, unsigned index)
      : dict(dict), it(it), index(index) {
      move_to_next_bucket();
    }

    friend Dictionary<K, V>;

    KeyValuePair<K, V>& operator*() {
      return *it;
    }
    
    const KeyValuePair<K, V>& operator*() const {
      return *it;
    }
    
    bool operator!=(const Iterator& other) const {
      return dict != other.dict || index != other.index || it != other.it;
    }

    Iterator& operator++() {
      ++it;
      move_to_next_bucket();

      return *this;
    }

  private:
    const Dictionary<K, V>* dict;
    typename Bucket::Iterator it;
    unsigned index;
  
    void move_to_next_bucket() {
      while (index < dict->data.capacity() && it == dict->data[index].end()) {
        ++index;
        if (index < dict->data.capacity()) {
          it = dict->data[index].begin();
        }
      }
    }
  };

  Iterator begin() const {
    return Iterator(this, data[0].begin(), 0);
  }

  Iterator end() const {
    return Iterator(this, data[data.capacity() - 1].end(), data.capacity());
  }

private:
  Hash hash;
  std::vector<Bucket> data;

  static constexpr float load_factor_threshold = 0.7;

  typename Bucket::Iterator bucket_find(const Bucket& bucket, const K& key) const {
    for (typename Bucket::Iterator it = bucket.begin(); it != bucket.end(); ++it) {
      if ((*it).key == key) {
        return it;
      }
    }

    return bucket.end();
  }

  double load_factor() const {
    return static_cast<float>(data.size()) / data.capacity();
  }

  void resize() {
    std::vector<Bucket> new_data(data.capacity() * 2);

    for (const KeyValuePair<K, V>& pair : *this) {
      unsigned index = hash(pair.key) % new_data.capacity();
      new_data[index].insert_last(pair);
    }

    data = std::move(new_data);
  }
};

// template <typename T>
// class Set : private Dictionary<T, bool> {
// public:
//   Set(const typename Dictionary<T, bool>::Hash& hash, std::size_t capacity = 128)
//     : Dictionary<T, bool>(hash, capacity) {}

//   void insert(const T& element) {
//     this->set(element, true);
//   }
// };

template <typename T>
class Set : public Dictionary<T, bool> {
public:
  Set(const typename Dictionary<T, bool>::Hash& hash, std::size_t capacity = 128)
    : Dictionary<T, bool>(hash, capacity) {}

  void insert(const T& element) {
    this->set(element, true);
  }
};


template <typename K, typename V>
class LRUCache {
public:
  using List = DoublyLinkedList<KeyValuePair<K, V>>;
  using Iterator = typename List::Iterator;

  LRUCache(std::size_t capacity) : capacity(capacity), dictionary(std::hash<K>{}) {}

  void insert(const K& key, const V& value) {
    std::optional<Iterator> it = dictionary.lookup(key);

    if (it.has_value()) {
      cache.remove_at(it.value());
      cache.insert_first({key, value});
      dictionary.set(key, cache.begin());
      return;
    }

    if (cache.get_size() == capacity) {
      Iterator lru = cache.last_i();
      dictionary.remove((*lru).key);
      cache.remove_last();  
    }

    cache.insert_first({key, value});
    dictionary.set(key, cache.begin());
  }

  std::optional<V> get(const K& key) {
    std::optional<Iterator> element = dictionary.lookup(key);

    if (!element.has_value()) {
      return std::nullopt;
    }

    V value = (*element.value()).value;
    cache.remove_at(element.value());
    cache.insert_first({key, value});
    dictionary.set(key, cache.begin());

    return value;
  }

  void evict(const K& key) {
    std::optional<Iterator> element = dictionary.lookup(key);

    if (!element.has_value()) {
      return;
    }

    cache.remove_at(element.value());
    dictionary.remove(key);
  }

private:
  Dictionary<K, Iterator> dictionary;
  List cache;
  std::size_t capacity;
};

int main() {
  Dictionary<std::string, int> dictionary(std::hash<std::string>{}, 1);

  dictionary.set("Hello", 2);
  dictionary.set("Goodbye", 8);
  dictionary.set("World", -4);

  dictionary.set("Goodbye", -8);
  dictionary.remove("Hello");

  for (const std::string& str : {"Hello", "Goodbye", "World", "End"}) {
    std::optional<int> n = dictionary.lookup(str);

    if (n.has_value()) {
      std::cout << str << " -> " << n.value() << '\n';
    } else {
      std::cout << "No key " << str << " in dictionary\n";
    }
  }

  for (const std::string& key : dictionary.keys()) {
    std::cout << key << ' ';
  }
  std::cout << '\n';
  
  for (int value : dictionary.values()) {
    std::cout << value << ' ';
  }
  std::cout << '\n';

  for (const KeyValuePair<std::string, int>& pair : dictionary) {
    std::cout << pair.key << ' ' << pair.value << '\n';
  }

  Set<int> set(std::hash<int>{});
  set.insert(7);
  set.insert(3);
  set.insert(4);
  set.insert(7);
  set.insert(4);

  for (int n : set.keys()) {
    std::cout << n << ' '; 
  }
  std::cout << '\n';
  return 0;
}