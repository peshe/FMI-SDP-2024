#include <algorithm>
#include <iostream>

struct Student
{
    std::string name;
    unsigned fn;
    unsigned score;
};

bool compareStudents(const Student &st1, const Student &st2)
{
    return st1.score == st2.score ? st1.fn < st2.fn : st1.score < st2.score;
}

int n, q;
Student students[100005];
unsigned minScore;

void binarySearch()
{
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].score >= minScore) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    std::cout << students[left].name << " " << students[left].fn << std::endl;
}

int main()
{
    std::cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        std::cin >> students[i].name >> students[i].fn >> students[i].score;
    }

    std::sort(students, students + n, compareStudents);

    for (int i = 0; i < q; ++i) {
        std::cin >> minScore;

        binarySearch();
    }

    return 0;
}