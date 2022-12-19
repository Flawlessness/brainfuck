#include "majority_strategy.h"

IStrategy :: result majority_strategy :: run(const std::vector<std::vector<bool>> &history, const int &row, const int &column) const
{
    if (row == 0)
    {
        return IStrategy :: result :: cooperate;
    }
    int cooperates_sum = 0;
    for(int k = 0; k < row; k++)
    {
        int cooperate = 1;
        for (int i = 0; i < 3; i++)
        {
            if (i == column)
            {
                continue;
            }
            if (history[k][i] == 0)
            {
                cooperate = 0;
            }
        }
        cooperates_sum += cooperate;
    }
    if (cooperates_sum >= (row / 2))
    {
        return IStrategy :: result :: cooperate;
    }
    else
    {
        return IStrategy :: result :: deflect;
    }

}