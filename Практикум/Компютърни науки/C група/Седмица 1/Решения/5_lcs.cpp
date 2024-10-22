#include <iostream>

std::string lcs(const std::string &s1, const std::string &s2)
{
    if (s1.empty() || s2.empty())
        return "";

    auto last_elem1 = s1[s1.length() - 1];
    auto last_elem2 = s2[s2.length() - 1];
    if (last_elem1 == last_elem2)
    {
        auto s1_popped_back = s1.substr(0, s1.length() - 1);
        auto s2_popped_back = s2.substr(0, s2.length() - 1);
        auto lcs_recursive_result = lcs(s1_popped_back, s2_popped_back);
        return lcs_recursive_result + last_elem1;
    }

    auto lcs_recursive_right_result = lcs(s1, s2.substr(0, s2.length() - 1));
    auto lcs_recursive_left_result = lcs(s1.substr(0, s1.length() - 1), s2);
    if (lcs_recursive_left_result.length() > lcs_recursive_right_result.length())
        return lcs_recursive_left_result;
    else
        return lcs_recursive_right_result;
}

int main()
{
    std::string s1;
    std::cin >> s1;
    if (!std::cin)
    {
        std::cerr << "error: input of first string failed" << std::endl;
        return 1;
    }

    std::string s2;
    std::cin >> s2;
    if (!std::cin)
    {
        std::cerr << "error: input of second string failed" << std::endl;
        return 2;
    }

    std::cout << lcs(s1, s2) << std::endl;

    return 0;
}