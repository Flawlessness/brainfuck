#include "deflect_always_strategy.h"

IStrategy :: result deflect_always_strategy :: run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const
{
    return IStrategy :: result :: deflect;
}