#include "cooperate_always_strategy.h"

IStrategy :: result cooperate_always_strategy :: run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    return IStrategy :: result :: cooperate;
}
