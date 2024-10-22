#include <iostream>
#include <vector>

void printIntVector(const std::vector<int>& v);

/* Solution function */
std::vector<int> mergeSorted(const std::vector<int>& x, const std::vector<int>& y)
{
    std::vector<int> result(x.size() + y.size());
    /* I am using the built-in iterators to not forget about them */
    std::vector<int>::const_iterator idx_x = x.begin(), idx_y = y.begin();
    std::vector<int>::iterator idx = result.begin();
    
    /* Traversing both arrays together */
    while (idx_x != x.end() && idx_y != y.end()) {
        /* Adding the smaller element to the result.
           When we have equal values we choose from x */

        if (*idx_x <= *idx_y) {
            *idx = *idx_x;
            ++idx_x;
        } else {
            *idx = *idx_y;
            ++idx_y;
        }

        ++idx;
    }

    /* After the cycle exactly one of the vectors is fully traversed */
    if (idx_x != x.end()) {
        while (idx_x != x.end()) {
            *idx = *idx_x;
            ++idx;
            ++idx_x;
        }
    } else {
        while (idx_y != y.end()) {
            *idx = *idx_y;
            ++idx;
            ++idx_y;
        }
    }

    return result;
}

int main()
{
    std::vector<int> a, b;
    /* Fill a and b */
    for (int i = 1; i < 100; i*=2) {
        a.push_back(i);
    }
    for (int i = 1; i < 100; i*=3) {
        b.push_back(i);
    }

    /* Check the content of a and b
    printIntVector(a);
    printIntVector(b);
    */ 

   /* Call the solution function */
    std::vector<int> sorted = mergeSorted(a, b);
    printIntVector(sorted);
    
    return 0;
}

void printIntVector(const std::vector<int>& v)
{
    for (const int el : v)
        std::cout << el << ' ';
    std::cout << std::endl;
}