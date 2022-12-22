#pragma once

#include "IStrategy.h"
#include <vector>

class tit_for_tat_forgiveness_strategy : public IStrategy
{
public:
    result run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const override;
};