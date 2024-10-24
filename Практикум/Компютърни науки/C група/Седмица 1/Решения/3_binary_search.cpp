#include <iostream>

template <typename T>
int binary_search_helper(T a[], T x, unsigned int l, unsigned int r)
{
    if (l == r)
        return -1;

    auto m = (l + r) / 2;
    if (x == a[m])
        return m;
    if (x < a[m])
        return binary_search_helper(a, x, l, m - 1);
    return binary_search_helper(a, x, m + 1, r);
}

template <typename T>
int binary_search(T a[], unsigned int n, T x)
{
    return binary_search_helper(a, x, 0, n - 1);
}

int main()
{
    int n;
    std::cin >> n;
    if (!std::cin)
    {
        std::cerr << "error: input of array size failed" << std::endl;
        return 1;
    }
    if (n < 0)
    {
        std::cerr << "error: array size should be a natural number" << std::endl;
        return 2;
    }

    // XXX: вместо ръчна деалокация преди всеки `return`, за предпочитане е да се опакова върнатият указател в `std::unique_ptr` обект, който да гарантира, че паметта, заделена за масива, ще се освободи
    auto *a = new int[n];
    for (unsigned int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        if (!std::cin)
        {
            std::cerr << "error: input of array element failed" << std::endl;
            delete[] a;
            return 3;
        }
    }

    int x;
    std::cin >> x;
    if (!std::cin)
    {
        std::cerr << "error: input of number for searching in array failed" << std::endl;
        delete[] a;
        return 4;
    }

    std::cout << binary_search(a, n, x) << std::endl;

    delete[] a;

    return 0;
}