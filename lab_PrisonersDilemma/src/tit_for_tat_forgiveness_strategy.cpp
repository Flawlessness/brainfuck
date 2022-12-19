#include "tit_for_tat_forgiveness_strategy.h"

IStrategy :: result tit_for_tat_forgiveness_strategy :: run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const
{
    bool result = true;
    if (row < 2)
    {
        return IStrategy :: result :: cooperate;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 2][i] == 0)
        {
            result = false;
        }
    }
    if (result)
    {
        return IStrategy :: result :: cooperate;
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 1][i] == 0)
        {
            return IStrategy :: result :: deflect;
        }
    }
    return IStrategy :: result :: cooperate;
}
