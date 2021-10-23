#pragma once
#include <vector>

#include "Point/Point.hpp"

struct IDataGetter {
	virtual ~IDataGetter() = default;

	[[nodiscard]] virtual std::vector<Point<double>> GetData() const = 0;

	[[nodiscard]] virtual double GetConfidenceProbability() const = 0;
};
