#include <iostream>

template <typename T>
void swap(T &x, T &y)
{
    T a = x;
    x = y;
    y = a;
}

// функцията не е шаблонна, тъй като в нея вътрешно се използват методите на `std::string`
void power_set_helper(std::string &a, size_t i)
{
    if (i == a.length() - 1)
    {
        std::cout << a << std::endl;
        return;
    }

    for (size_t j = i; j < a.length(); j++)
    {
        swap(a[i], a[j]);
        power_set_helper(a, i + 1);
        swap(a[i], a[j]);
    }
}

void power_set(std::string &a)
{
    power_set_helper(a, 0);
}

int main()
{
    std::string a;
    std::cin >> a;
    if (!std::cin)
    {
        std::cerr << "error: input of character array failed" << std::endl;
        return 1;
    }

    power_set(a);

    return 0;
}