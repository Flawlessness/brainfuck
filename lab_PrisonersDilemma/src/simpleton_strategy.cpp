#include "simpleton_strategy.h"

bool simpleton_strategy :: run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    if (row == 0)
    {
        return true;
    }
    if (history[row - 1][column] == 0)
    {
        return false;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 1][i] == 0)
        {
            return false;
        }
    }
    return true;
}