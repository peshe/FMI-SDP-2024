#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct Dancer
{
    char gender;
    std::string name;
};

// Function to print remaining dancers (generic for both males and females)
void printRemainingDancers(std::queue<Dancer> &dancerQueue, const std::string &gender)
{
    if (!dancerQueue.empty())
    {
        std::cout << "Remaining " << gender << " dancers waiting to dance:";
        while (!dancerQueue.empty())
        {
            std::cout << " " << dancerQueue.front().name;
            dancerQueue.pop();
            if (!dancerQueue.empty())
            {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}

// Function to pair dancers
void pairDancers(std::queue<Dancer> &femaleQueue, std::queue<Dancer> &maleQueue)
{
    std::vector<std::pair<Dancer, Dancer>> pairs;

    while (!femaleQueue.empty() && !maleQueue.empty())
    {
        Dancer female = femaleQueue.front();
        Dancer male = maleQueue.front();
        pairs.emplace_back(female, male);
        femaleQueue.pop();
        maleQueue.pop();
    }

    for (const auto &pair : pairs)
    {
        std::cout << "Female dancer is: " << pair.first.name
                  << " and the male dancer is: " << pair.second.name << std::endl;
    }

    printRemainingDancers(femaleQueue, "female");
    printRemainingDancers(maleQueue, "male");
}

std::vector<Dancer> inputDancers()
{
    std::vector<Dancer> dancers;
    std::string input;

    std::cout << "Enter dancers (format: F Name or M Name). Type any other character to finish:" << std::endl;

    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty() || (input[0] != 'F' && input[0] != 'M'))
        {
            break;
        }

        Dancer dancer;
        dancer.gender = input[0];
        dancer.name = input.substr(2);

        dancers.push_back(dancer);
    }

    return dancers;
}

int main()
{
    std::vector<Dancer> dancers = inputDancers();

    std::queue<Dancer> femaleQueue;
    std::queue<Dancer> maleQueue;

    for (const auto &dancer : dancers)
    {
        if (dancer.gender == 'F')
        {
            femaleQueue.push(dancer);
        }
        else
        {
            maleQueue.push(dancer);
        }
    }

    pairDancers(femaleQueue, maleQueue);

    return 0;
}
