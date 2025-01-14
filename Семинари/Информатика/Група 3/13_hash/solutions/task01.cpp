
#include <iostream>
#include <vector>
#include <list>

template <class Key, class Value, class HashFunction = std::hash<Key>>
class HashTable
{
public:
    HashTable(std::size_t maxSize);
    bool containsKey(const Key&);
    Value get(const Key&);
    void put(const Key&, const Value&);
    bool empty() const;
    int size() const;
    void remove(const Key&);

// Task 2
public:
    std::vector<Key> keys();
    std::vector<Value> values();
    double efficiency();

private:
    std::vector<std::list<std::pair<Key, Value>>> table;

    std::size_t maxSize;

    HashFunction hash;

private:
    std::size_t getIndex(const Key& k);
    std::list<std::pair<Key, Value>>& getBucket(const Key& k);
    std::pair<Key, Value>* locatePair(const Key& k);
};

template<class Key, class Value, class HashFunction>
std::size_t HashTable<Key, Value, HashFunction>::getIndex(const Key& k)
{
    std::size_t hashValue = hash(k);
    return hashValue % maxSize;
}

template<class Key, class Value, class HashFunction>
std::list<std::pair<Key, Value>>& HashTable<Key, Value, HashFunction>::getBucket(const Key& k)
{
    return this->table[this->getIndex(k)];
}

template<class Key, class Value, class HashFunction>
std::pair<Key, Value>* HashTable<Key, Value, HashFunction>::locatePair(const Key& key)
{
    std::list<std::pair<Key, Value>>& bucket = this->getBucket(key);

    for (std::pair<Key, Value>& pair : bucket) {
        if (pair.first == key) {
            return &pair;
        }
    }

    return nullptr;
}

template<class Key, class Value, class HashFunction>
HashTable<Key, Value, HashFunction>::HashTable(std::size_t maxSize)
    : table(maxSize), maxSize(maxSize) {}

template<class Key, class Value, class HashFunction>
bool HashTable<Key, Value, HashFunction>::containsKey(const Key& key)
{
    return this->locatePair(key) != nullptr;
}

template<class Key, class Value, class HashFunction>
Value HashTable<Key, Value, HashFunction>::get(const Key& key)
{
    std::pair<Key, Value>* pair = this->locatePair(key);
    if (!pair) {
        throw std::out_of_range("Key doesn't exist in table");
    }

    return pair->second;
}

template<class Key, class Value, class HashFunction>
void HashTable<Key, Value, HashFunction>::put(const Key& key, const Value& value)
{
    std::pair<Key, Value>* pair = this->locatePair(key);
    if (pair != nullptr) {
        pair->second = value;
        return;
    }

    this->getBucket(key).emplace_back(key, value);
    // this->getBucket(key).push_back(std::pair<Key, Value>(key, value));
    // this->getBucket(key).push_back({ key, value });
}

template<class Key, class Value, class HashFunction>
bool HashTable<Key, Value, HashFunction>::empty() const
{
    return this->size() == 0;
}

template<class Key, class Value, class HashFunction>
int HashTable<Key, Value, HashFunction>::size() const
{
    int result = 0;
    for (const auto& bucket : this->table) {
        result += bucket.size();
    }

    return result;
}

template<class Key, class Value, class HashFunction>
void HashTable<Key, Value, HashFunction>::remove(const Key& key)
{
    std::list<std::pair<Key, Value>>& bucket = this->getBucket(key);

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if ((*it).first == key) {
            bucket.erase(it);
            return;
        }
    }
}

template<class Key, class Value, class HashFunction>
std::vector<Key> HashTable<Key, Value, HashFunction>::keys() {
    std::vector<Key> result;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        for (const std::pair<Key, Value> &pair : bucket)
            result.push_back(pair.first);
    }

    return result;
}

template<class Key, class Value, class HashFunction>
std::vector<Value> HashTable<Key, Value, HashFunction>::values() {
    std::vector<Value> result;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        for (const std::pair<Key, Value> &pair : bucket)
            result.push_back(pair.second);
    }

    return result;
}

template<class Key, class Value, class HashFunction>
double HashTable<Key, Value, HashFunction>::efficiency() {
    int all = 0;
    int colliding = 0;

    for (const std::list<std::pair<Key, Value>> &bucket : table)
    {
        if (bucket.size() > 1)
            colliding += bucket.size();

        all += bucket.size();
    }

    return colliding * 1.0 / all;
}

int main()
{
    HashTable<std::string, int> ht(100);

    std::cout << ht.size() << std::endl;
    ht.put("pesho", 2);
    ht.put("gosho", 6);
    ht.put("ivan", 3);
    std::cout << ht.size() << std::endl;
    std::cout << std::boolalpha<< ht.containsKey("ivan") << std::endl;
    std::cout << std::boolalpha << ht.containsKey("stoyan") << std::endl;
    std::cout << ht.get("ivan") << std::endl;
    ht.put("ivan", 5);
    std::cout << ht.get("ivan") << std::endl;

    std::cout << ht.efficiency() << std::endl;
}
