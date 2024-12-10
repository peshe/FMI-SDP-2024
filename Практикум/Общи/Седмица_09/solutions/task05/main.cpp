#include <vector>

#include "TreeSet.hpp"


using std::vector;


int countUniques(const vector<int>& data) {
    Set<int>* dataset = new TreeSet<int>;

    for (int element : data) {
        dataset->add(element);
    }

    int result = dataset->size();
    delete dataset;
    return result;
}

bool twoSum(const vector<int>& data, int target) {
    TreeSet<int> dataset;

    for (int element : data) {
        if (dataset.contains(target - element)) {
            return true;
        }
        dataset.add(element);
    }

    return false;
}

int main() {
    vector<int> t1 = {1, 1, 1, 1, 1};
    assert(countUniques(t1) == 1);
    assert(!twoSum(t1, 1));
    assert(twoSum(t1, 2));
    assert(!twoSum(t1, 3));

    vector<int> t2 = {1, 2, 3, 4, 5};
    assert(countUniques(t2) == 5);
    assert(twoSum(t2, 5));
    assert(!twoSum(t2, 10));

    vector<int> t3 = {1, 2, 1, 2, 1};
    assert(countUniques(t3) == 2);
    assert(!twoSum(t3, 1));
    assert(twoSum(t3, 2));
    assert(twoSum(t3, 3));
    assert(twoSum(t3, 4));
    assert(!twoSum(t3, 5));

    return 0;
}
