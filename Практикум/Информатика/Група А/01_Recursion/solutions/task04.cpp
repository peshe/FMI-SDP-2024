#include <iostream>
#include <vector>

void print(const std::vector<int> &list) {
    std::cout << "{\t";
    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << '\t';
    }
    std::cout << "}\n";
}

void generatePermutation(const std::vector<int> &set, std::vector<int> &permutation, std::vector<bool> &used,
                         std::size_t currentIndex = 0) {
    if (currentIndex == set.size()) {
        print(permutation);
    }

    // For each element which hasn't been used
    for (std::size_t i = 0; i < set.size(); ++i) {
        if (!used[i]) {
            // Add said element at this position
            permutation.push_back(set[i]);
            used[i] = true;
            // Permute the rest
            generatePermutation(set, permutation, used, currentIndex + 1);
            // Restore to previous state
            used[i] = false;
            permutation.pop_back();
        }
    }
}

void permutationWrapper(const std::vector<int> &set) {
    std::vector<int> permutation;
    std::vector<bool> usedItems(set.size());

    generatePermutation(set, permutation, usedItems);
}

int main() {
    const std::vector<int> sampleSet = {1, 8, 3};
    permutationWrapper(sampleSet);

    return 0;
}
