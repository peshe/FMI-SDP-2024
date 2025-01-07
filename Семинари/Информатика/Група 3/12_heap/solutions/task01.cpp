#include <iostream>
#include <vector>

void printVector(const std::vector<int> &arr) {
    for (int item: arr) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
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

void buildMaxHeap(std::vector<int> &arr) {
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        maxHeapify(arr, i);
}

int main() {
    std::vector<int> sample = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};

    printVector(sample);

    buildMaxHeap(sample);

    printVector(sample);

    return 0;
}
