#include "scoundrel_strategy.h"

IStrategy :: result scoundrel_strategy :: run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    if (row == 0)
    {
        return IStrategy :: result :: deflect;
    }
    int flag = 1;
    for (int i = 0; i < 3; i++)
    {
        if (i == column)
        {
            continue;
        }
        if (history[row - 1][i] == 0)
        {
            flag = 0;
        }
    }
    if (flag == 1)
    {
        if (history[row-1][column] == 0)
        {
            return IStrategy :: result :: cooperate;
        }
        else
        {
            return IStrategy :: result :: deflect;
        }
    }
    else
    {
        return IStrategy :: result :: deflect;
    }
}