#include <iostream>
#include <vector>

void print(const std::vector<int> &list) {
    std::cout << "{\t";
    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << '\t';
    }
    std::cout << "}\n";
}

void generateVariation(const std::vector<int> &set, std::vector<int> &variation, std::vector<bool> &used,
                       int k, std::size_t currentIndex = 0) {
    if (currentIndex == k) {
        print(variation);
    }

    // For each element which hasn't been used
    for (std::size_t i = 0; i < set.size(); ++i) {
        if (!used[i]) {
            // Add said element at this position
            variation.push_back(set[i]);
            used[i] = true;
            // Permute the rest
            generateVariation(set, variation, used, k, currentIndex + 1);
            // Restore to previous state
            used[i] = false;
            variation.pop_back();
        }
    }
}

void variationWrapper(const std::vector<int> &set, int k) {
    std::vector<int> variation;
    std::vector<bool> usedItems(set.size());

    generateVariation(set, variation, usedItems, k);
}

int main() {
    const std::vector<int> sampleSet = {1, 8, 3};
    variationWrapper(sampleSet, 2);

    return 0;
}
