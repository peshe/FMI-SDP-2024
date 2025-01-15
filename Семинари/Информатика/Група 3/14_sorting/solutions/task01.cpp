#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& v) {
    std::size_t size = v.size();
    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

void bubbleSort2(std::vector<int>& v) {
    std::size_t size = v.size();
    std::size_t right = size - 1;
    for (std::size_t i = 0; i < size; ++i) {
        std::size_t lastSwappedIndex = 0;
        for (std::size_t j = 0; j < right; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                lastSwappedIndex = j;
            }
        }
        right = lastSwappedIndex;
    }
}

int main() {
    std::vector<int> v = {2, 1,-3, 11, 7, 0, 5, 4, 1};
    // bubbleSort(v);
    bubbleSort2(v);
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
