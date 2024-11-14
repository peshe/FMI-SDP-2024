#include <iostream>

static const std::string DIGIT_LETTER_MAPPING[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void letter_combinations(const std::string &phone_num, std::string letter_combination, size_t i)
{
    if (i == phone_num.length())
    {
        std::cout << letter_combination << std::endl;
        return;
    }

    auto digit = phone_num[i];
    if (digit < '2' || digit > '9')
    {
        std::cerr << "errror: invalid digit in phone number: " << digit << std::endl;
        return;
    }

    auto digit_index = digit - '2';
    for (auto letter : DIGIT_LETTER_MAPPING[digit_index])
    {
        letter_combination.push_back(letter);
        letter_combinations(phone_num, letter_combination, i + 1);
        letter_combination.pop_back();
    }
}

void letter_combinations(const std::string &phone_num)
{
    letter_combinations(phone_num, "", 0);
}

int main()
{
    std::string phone_num;
    std::getline(std::cin, phone_num);
    if (!std::cin)
    {
        std::cerr << "error: input of phone number failed" << std::endl;
        return 1;
    }

    letter_combinations(phone_num);

    return 0;
}