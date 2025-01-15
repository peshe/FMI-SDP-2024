#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

double xPancho, yPancho;
double xDrown, yDrown;
double vSand, vWater;

double calculateTime(double midPoint)
{
    double distanceOnSand = std::sqrt(std::pow(yPancho, 2) + std::pow(midPoint - xPancho, 2));
    double distanceInWater = std::sqrt(std::pow(yDrown, 2) + std::pow(midPoint - xDrown, 2));

    return distanceOnSand / vSand + distanceInWater / vWater;
}

void ternarySearch()
{
    double eps = 0.001;
    double left = std::min(xPancho, xDrown);
    double right = std::max(xPancho, xDrown);
    double mid1;
    double mid2;
    while (right - left > eps) {
        mid1 = left + (right - left) / 3;
        mid2 = right - (right - left) / 3;

        double time1 = calculateTime(mid1);
        double time2 = calculateTime(mid2);
        if (time1 < time2) {
            right = mid2;
        } else {
            left = mid1;
        }
    }
    std::cout << std::setprecision(5) << std::fixed << calculateTime(left) << std::endl;
}

int main()
{
    int queryCount;
    std::cin >> queryCount;

    for (int i = 0; i < queryCount; ++i) {
        std::cin >> xPancho >> yPancho;
        std::cin >> xDrown >> yDrown;
        std::cin >> vSand >> vWater;

        ternarySearch();
    }
    return 0;
}