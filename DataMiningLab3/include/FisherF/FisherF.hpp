#pragma once
#include <map>
#include <random>

class FisherF {
private:
	static const std::map<double, std::map<std::pair<int, int>, double>> TABLE;

public:
	explicit FisherF(int k1, int k2) : k1_(k1), k2_(k2) {
		
	}

	[[nodiscard]] double GetFStatistics(double x) const {
		return FisherF::TABLE.lower_bound(x - std::numeric_limits<double>::epsilon())->second.at({ this->k1_, this->k2_ });
	}

private:
	int k1_, k2_;
};

const std::map<double, std::map<std::pair<int, int>, double>> FisherF::TABLE
	= std::map {
		std::pair {
			0.05, std::map {
				std::pair {
					std::pair{1, 1}, 161.4
				},
				std::pair {
					std::pair{1, 2}, 18.51
				},
				std::pair {
					std::pair{1, 3}, 10.13
				},
				std::pair {
					std::pair{1, 4}, 7.71
				},
				std::pair {
					std::pair{1, 5}, 6.61
				},
				std::pair {
					std::pair{1, 6}, 5.99
				},
				std::pair {
					std::pair{1, 7}, 5.59
				},
				std::pair {
					std::pair{1, 8}, 5.32
				},
				std::pair {
					std::pair{1, 9}, 5.12
				},
				std::pair {
					std::pair{1, 10}, 4.96
				},
				std::pair {
					std::pair{1, 11}, 4.84
				},
				std::pair {
					std::pair{1, 12}, 4.75
				},
				std::pair {
					std::pair{1, 13}, 4.67
				},
				std::pair {
					std::pair{1, 14}, 4.60
				},
				std::pair {
					std::pair{1, 15}, 4.54
				},
				std::pair {
					std::pair{1, 16}, 4.49
				},
				std::pair {
					std::pair{1, 17}, 4.45
				},
				std::pair {
					std::pair{1, 18}, 4.41
				},
				std::pair {
					std::pair{1, 19}, 4.38
				},
				std::pair {
					std::pair{1, 20}, 4.35
				},
				std::pair {
					std::pair{1, 21}, 4.32
				},
				std::pair {
					std::pair{1, 22}, 4.30
				},
				std::pair {
					std::pair{1, 23}, 4.28
				},
				std::pair {
					std::pair{1, 24}, 4.26
				},
				std::pair {
					std::pair{1, 25}, 4.24
				},
				std::pair {
					std::pair{1, 26}, 4.23
				},
				std::pair {
					std::pair{1, 27}, 4.21
				},
				std::pair {
					std::pair{1, 28}, 4.20
				},
				std::pair {
					std::pair{1, 29}, 4.18
				},
				std::pair {
					std::pair{1, 30}, 4.17
				},
				std::pair {
					std::pair{1, 40}, 4.08
				},
				std::pair {
					std::pair{1, 60}, 4.00
				},
				std::pair {
					std::pair{1, 120}, 3.92
				},
				std::pair {
					std::pair{1, std::numeric_limits<int>::infinity()}, 3.84
				}
			}
		},
		std::pair {
			0.10, std::map {
				std::pair {
					std::pair{1, 1}, 39.86
				},
				std::pair {
					std::pair{1, 2}, 8.53
				},
				std::pair {
					std::pair{1, 3}, 5.54
				},
				std::pair {
					std::pair{1, 4}, 4.54
				},
				std::pair {
					std::pair{1, 5}, 4.06
				},
				std::pair {
					std::pair{1, 6}, 3.78
				},
				std::pair {
					std::pair{1, 7}, 3.59
				},
				std::pair {
					std::pair{1, 8}, 3.46
				},
				std::pair {
					std::pair{1, 9}, 3.36
				},
				std::pair {
					std::pair{1, 10}, 3.29
				},
				std::pair {
					std::pair{1, 11}, 3.23
				},
				std::pair {
					std::pair{1, 12}, 3.18
				},
				std::pair {
					std::pair{1, 13}, 3.14
				},
				std::pair {
					std::pair{1, 14}, 3.10
				},
				std::pair {
					std::pair{1, 15}, 3.07
				},
				std::pair {
					std::pair{1, 16}, 3.05
				},
				std::pair {
					std::pair{1, 17}, 3.03
				},
				std::pair {
					std::pair{1, 18}, 3.01
				},
				std::pair {
					std::pair{1, 19}, 2.99
				},
				std::pair {
					std::pair{1, 20}, 2.97
				},
				std::pair {
					std::pair{1, 21}, 2.96
				},
				std::pair {
					std::pair{1, 22}, 2.95
				},
				std::pair {
					std::pair{1, 23}, 2.94
				},
				std::pair {
					std::pair{1, 24}, 2.93
				},
				std::pair {
					std::pair{1, 25}, 2.92
				},
				std::pair {
					std::pair{1, 26}, 2.91
				},
				std::pair {
					std::pair{1, 27}, 2.90
				},
				std::pair {
					std::pair{1, 28}, 2.89
				},
				std::pair {
					std::pair{1, 29}, 2.89
				},
				std::pair {
					std::pair{1, 30}, 2.88
				},
				std::pair {
					std::pair{1, 40}, 2.84
				},
				std::pair {
					std::pair{1, 60}, 2.79
				},
				std::pair {
					std::pair{1, 120}, 2.75
				},
				std::pair {
					std::pair{1, std::numeric_limits<int>::infinity()}, 2.71
				}
			}
		},
		std::pair {
			0.25, std::map {
				std::pair {
					std::pair{1, 1}, 5.83
				},
				std::pair {
					std::pair{1, 2}, 2.57
				},
				std::pair {
					std::pair{1, 3}, 2.02
				},
				std::pair {
					std::pair{1, 4}, 1.81
				},
				std::pair {
					std::pair{1, 5}, 1.69
				},
				std::pair {
					std::pair{1, 6}, 1.62
				},
				std::pair {
					std::pair{1, 7}, 1.57
				},
				std::pair {
					std::pair{1, 8}, 1.54
				},
				std::pair {
					std::pair{1, 9}, 1.51
				},
				std::pair {
					std::pair{1, 10}, 1.49
				},
				std::pair {
					std::pair{1, 11}, 1.47
				},
				std::pair {
					std::pair{1, 12}, 1.46
				},
				std::pair {
					std::pair{1, 13}, 1.45
				},
				std::pair {
					std::pair{1, 14}, 1.44
				},
				std::pair {
					std::pair{1, 15}, 1.43
				},
				std::pair {
					std::pair{1, 16}, 1.42
				},
				std::pair {
					std::pair{1, 17}, 1.42
				},
				std::pair {
					std::pair{1, 18}, 1.41
				},
				std::pair {
					std::pair{1, 19}, 1.41
				},
				std::pair {
					std::pair{1, 20}, 1.40
				},
				std::pair {
					std::pair{1, 21}, 1.40
				},
				std::pair {
					std::pair{1, 22}, 1.40
				},
				std::pair {
					std::pair{1, 23}, 1.39
				},
				std::pair {
					std::pair{1, 24}, 1.39
				},
				std::pair {
					std::pair{1, 25}, 1.39
				},
				std::pair {
					std::pair{1, 26}, 1.38
				},
				std::pair {
					std::pair{1, 27}, 1.38
				},
				std::pair {
					std::pair{1, 28}, 1.38
				},
				std::pair {
					std::pair{1, 29}, 1.38
				},
				std::pair {
					std::pair{1, 30}, 1.38
				},
				std::pair {
					std::pair{1, 40}, 1.36
				},
				std::pair {
					std::pair{1, 60}, 1.35
				},
				std::pair {
					std::pair{1, 120}, 1.34
				},
				std::pair {
					std::pair{1, std::numeric_limits<int>::infinity()}, 1.32
				}
			}
		},
	};