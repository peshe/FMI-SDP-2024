#include <iostream>
#include <iomanip>

static const size_t NUM_POSITIONS_HOUR = 4;
static const size_t NUM_POSITIONS_MINUTE = 6;

void binary_watch_combinations_hours_minutes(unsigned int turned_on_count, unsigned int current_turned_on_count, unsigned int minutes, unsigned int hours, size_t position_hour)
{
    if (minutes >= 60 || hours >= 12)
    {
        return;
    }

    if (current_turned_on_count == turned_on_count)
    {
        std::cout << hours << ":" << std::setfill('0') << std::setw(2) << minutes << std::endl;
        return;
    }

    if (position_hour == NUM_POSITIONS_HOUR)
    {
        return;
    }

    binary_watch_combinations_hours_minutes(turned_on_count, current_turned_on_count + 1, minutes, hours + (1 << position_hour), position_hour + 1);
    binary_watch_combinations_hours_minutes(turned_on_count, current_turned_on_count, minutes, hours, position_hour + 1);
}

void binary_watch_combinations_minutes(unsigned int turned_on_count, unsigned int current_turned_on_count, unsigned int minutes, size_t position_minute)
{
    if (minutes >= 60)
    {
        return;
    }

    if (current_turned_on_count == turned_on_count)
    {
        std::cout << "0:" << std::setfill('0') << std::setw(2) << minutes << std::endl;
        return;
    }

    if (position_minute == NUM_POSITIONS_MINUTE)
    {
        binary_watch_combinations_hours_minutes(turned_on_count, current_turned_on_count, minutes, 0, 0);
        return;
    }

    binary_watch_combinations_minutes(turned_on_count, current_turned_on_count + 1, minutes + (1 << position_minute), position_minute + 1);
    binary_watch_combinations_minutes(turned_on_count, current_turned_on_count, minutes, position_minute + 1);
}

void binary_watch_combinations(unsigned int turned_on_count)
{
    binary_watch_combinations_minutes(turned_on_count, 0, 0, 0);
}

int main()
{
    int turned_on_count;
    std::cin >> turned_on_count;
    if (!std::cin)
    {
        std::cerr << "error: input failed" << std::endl;
        return 1;
    }
    if (turned_on_count < 0)
    {
        std::cerr << "error: input should be a natural number" << std::endl;
        return 2;
    }

    binary_watch_combinations(turned_on_count);

    return 0;
}