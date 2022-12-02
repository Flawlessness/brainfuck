#include "random_strategy.h"
#include <random>

bool random_strategy ::run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(0,1);
    return dist6(rng);
}
