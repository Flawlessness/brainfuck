#include "tit_for_tat_forgiveness_strategy.h"

bool tit_for_tat_forgiveness_strategy :: run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const
{
    bool result = 1;
    if (row < 2)
    {
        return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 2][i] == 0)
        {
            result = 0;
        }
    }
    if (result == 1)
    {
        return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 1][i] == 0)
        {
            return 0;
        }
    }
    return 1;
}
