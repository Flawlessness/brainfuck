#include "tit_for_tat_strategy.h"

bool tit_for_tat_strategy ::run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    if (row == 0)
    {
        return true;
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
