#pragma once

#include <vector>

class IStrategy
{
public:
    enum class result{deflect, cooperate};
	virtual ~IStrategy() = default;
	virtual result run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const = 0;

};
