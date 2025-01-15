#include <iostream>
#include <vector>

void quickSortIdea(std::vector<int> &v) {
    if (v.size() == 0) return;

    std::vector<int> smaller;
    std::vector<int> same;
    std::vector<int> larger;
    auto chosenItem = v[v.size() / 2];
    for (auto &i: v) {
        if (i < chosenItem)
            smaller.push_back(std::move(i));
        else if (chosenItem < i)
            larger.push_back(std::move(i));
        else
            same.push_back(std::move(i));
    }
    quickSortIdea(smaller);
    quickSortIdea(larger);

    std::move(begin(smaller), end(smaller), begin(v));
    std::move(begin(same), end(same), begin(v) + smaller.size());
    std::move(begin(larger), end(larger), end(v) - larger.size());
}

/**
* Return median of left, center, and right.
* Order these and hide the pivot.
*/
template<typename Comparable>
const Comparable &median3(std::vector<Comparable> &a, int left, int right) {
    int center = (left + right) / 2;
    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);

    return a[right - 1];
}

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template<typename Comparable>
void quickSort(std::vector<Comparable> &a, int left, int right) {
    if (left + 10 <= right) {
        const Comparable &pivot = median3(a, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for (; ;) {
            while (a[++i] < pivot) {
            }
            while (pivot < a[--j]) {
            }
            if (i < j) {
                std::swap(a[i], a[j]);
            } else {
                break;
            }
        }
        std::swap(a[i], a[right - 1]); // Restore pivot
        quickSort(a, left, i - 1); // Sort small elements
        quickSort(a, i + 1, right); // Sort large elements
    } else {
        // Do an insertion sort on the subarray
        insertionSort(a, left, right);
    }
}

// Driver function
template<typename Comparable>
void quickSort(std::vector<Comparable> &arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int main() {
    std::vector<int> v = {2, 1, -3, 11, 7, 0, 5, 4, 1};
    quickSort(v);
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
