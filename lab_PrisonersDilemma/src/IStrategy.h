#pragma once
#include <vector>

class IStrategy
{
public:
	virtual ~IStrategy() = default;

	virtual bool run(const std :: vector<std :: vector<bool>> &history, const int &row, const int &column) const = 0;

};