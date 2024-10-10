#include <iostream>

std::size_t plus3(std::size_t current) {
    return current + 3;
}

int sum(int arr[], std::size_t size, std::size_t (*next)(std::size_t)) {
    int sum = 0;
    for (std::size_t i = 0; i < size ; i = next(i)) {
        sum += arr[i];
    }
    return sum;
}

void map(int arr[], std::size_t size, int (*op)(int)) {
    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = op(arr[i]);
    }
}

struct FilteredResult {
    int* arr;
    std::size_t size;
};

FilteredResult filter(int arr[], std::size_t size, bool (*pred)(int)) {
    std::size_t count = 0;
    for (std::size_t i = 0; i < size; ++i) {
        if(pred(arr[i])) {
            count++;
        }
    }
    int* result = new int[count];
    std::size_t resIndex = 0;
    for (std::size_t i = 0; i < size; ++i) {
        if(pred(arr[i])) {
            result[resIndex] = arr[i];
            resIndex++;
        }
    }

    return FilteredResult {result, count};
}

bool isOdd(int x){
    return x % 2 == 1;
}

int main() {
    int sampleArr[] = {1, 2, 3, 4, 5, 6};
    std::cout << sum(sampleArr, 6, plus3);

    std::cout << std::endl;
    FilteredResult res = filter(sampleArr, 6, isOdd);
    for(std::size_t i = 0; i < res.size; ++i) {
        std::cout << res.arr[i] << '\t';
    }

    delete[] res.arr;

    return 0;
}
