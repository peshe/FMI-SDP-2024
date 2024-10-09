#include <iostream>

bool winningSequenceDFS(int arr[], std::size_t size, bool visited[],
                          int previous, std::size_t remaining) {
    if (remaining == 0) {
        return true;
    }
    for (std::size_t i = 0; i < size; ++i) {
        if (!visited[i] && (arr[i] % previous == 0 || previous % arr[i] == 0)) {
            visited[i] = true;

            if (winningSequenceDFS(arr, size, visited,
                                     arr[i], remaining - 1)) {
                return true;
            }

            visited[i] = false;
        }
    }
    return false;
}

bool winningSequence(int arr[], std::size_t size) {
    bool *visited = new bool[size];

    // Choose an element to remove first
    for (std::size_t i = 0; i < size; ++i) {
        visited[i] = true;
        if (winningSequenceDFS(arr, size, visited, arr[i], size - 1)) {
            delete[] visited;
            return true;
        }
        visited[i] = false;
    }
    delete[] visited;
    return false;
}


int main() {
    int sequence[]{13, 42, 17, 1, 3, 30, 10, 2, 6, 34, 2};
    std::cout << std::boolalpha << winningSequence(sequence, 11); // -> true

    return 0;
}
