#include <iostream>
#include <vector>
#include <queue>

void printVector(const std::vector<int> &arr) {
    for (int item: arr) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
}

std::vector<int> mergeHeapsNaive(std::vector<int> &a, std::vector<int> &b) {
    std::priority_queue<int> maxHeap;

    for (int i: a) {
        maxHeap.push(i);
    }

    for (int i: b) {
        maxHeap.push(i);
    }

    std::vector<int> merged;

    while (!maxHeap.empty()) {
        merged.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return merged;
}

void maxHeapify(std::vector<int> &arr, int rootIdx) {
    if (rootIdx >= arr.size())
        return;

    int leftIdx = 2 * rootIdx + 1;
    int rightIdx = 2 * rootIdx + 2;
    int maxIdx = rootIdx;

    if (leftIdx < arr.size() && arr[leftIdx] > arr[rootIdx])
        maxIdx = leftIdx;
    if (rightIdx < arr.size() && arr[rightIdx] > arr[maxIdx])
        maxIdx = rightIdx;

    if (maxIdx != rootIdx) {
        std::swap(arr[maxIdx], arr[rootIdx]);
        maxHeapify(arr, maxIdx);
    }
}

void buildMaxHeap(std::vector<int> &arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, i);
}

std::vector<int> mergeHeaps(std::vector<int> &a, std::vector<int> &b) {
    std::vector<int> merged;
    merged.reserve(a.size() + b.size());
    merged.insert(merged.end(), a.begin(), a.end());
    merged.insert(merged.end(), b.begin(), b.end());

    buildMaxHeap(merged, merged.size());
    return merged;
}


int main() {
    std::vector<int> a = {10, 5, 6, 2};
    std::vector<int> b = {12, 7, 9};


    auto result = mergeHeaps(a, b);
    printVector(result);

    return 0;
}
