#include <iostream>

// функцията не е шаблонна, тъй като в нея вътрешно се използват методите на `std::string`
void power_set(std::string s, std::string &processed)
{
    if (s.empty())
    {
        std::cout << processed << std::endl;
        return;
    }

    auto elem = s[0];
    s.erase(s.begin());
    power_set(s, processed);
    processed.push_back(elem);
    power_set(s, processed);
    processed.pop_back();
}

void power_set(const std::string &s)
{
    std::string processed;
    power_set(s, processed);
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