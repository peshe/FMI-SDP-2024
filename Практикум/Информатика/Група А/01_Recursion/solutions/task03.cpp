#include <iostream>
#include <vector>

void printVectorWithMask(const std::vector<int> &list, const std::vector<bool> &mask) {
    std::cout << "{\t";
    for (std::size_t i = 0; i < list.size(); ++i) {
        if (mask[i]) {
            std::cout << list[i] << '\t';
        }
    }
    std::cout << "}\n";
}

void
generateSubsetsRecursive(const std::vector<int> &set, std::vector<bool> subsetMask, std::size_t currentIndex = 0) {
    if (currentIndex == set.size()) {
        printVectorWithMask(set, subsetMask);
        return;
    }

    // Exclude current element
    subsetMask.push_back(0);
    generateSubsetsRecursive(set, subsetMask, currentIndex + 1);
    // Include current element
    subsetMask.pop_back();
    subsetMask.push_back(1);
    generateSubsetsRecursive(set, subsetMask, currentIndex + 1);
}

void subsetRecursiveWrapper(const std::vector<int> &set) {
    std::vector<bool> mask;
    generateSubsetsRecursive(set, mask);
}

int main() {
    const std::vector<int> sampleSet = {1, 8, 3};
    subsetRecursiveWrapper(sampleSet);

    return 0;
}
