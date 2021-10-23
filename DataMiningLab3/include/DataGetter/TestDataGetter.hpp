#pragma once
#include <memory>

#include "IDataGetter.hpp"

class TestDataGetter : public IDataGetter {
private:
	static const std::unique_ptr<std::vector<Point<double>>> DATA;
	static constexpr double CONFIDENCE_PROBABILITY = 0.95;

public:
	[[nodiscard]] std::vector<Point<double>> GetData() const override {
		return *TestDataGetter::DATA;
	}

	[[nodiscard]] double GetConfidenceProbability() const override {
		return TestDataGetter::CONFIDENCE_PROBABILITY;
	}
};

const std::unique_ptr<std::vector<Point<double>>> TestDataGetter::DATA
	= std::make_unique<std::vector<Point<double>>>(
		std::vector{
			Point<double>(1.0, 0.0),
			Point<double>(-1.0, -2.0),
			Point<double>(1.0, 1.0),
			Point<double>(1.0, 0.0),
			Point<double>(-1.0, -2.0),
			Point<double>(0.0, -1.0)
		}
	);
