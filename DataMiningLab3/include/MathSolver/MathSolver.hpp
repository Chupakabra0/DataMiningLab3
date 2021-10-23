#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "Point/Point.hpp"

template<class T> requires
	std::is_arithmetic_v<T> &&
	(!std::is_same_v<T, bool>) &&
	(!std::is_same_v<T, char>) &&
	(!std::is_same_v<T, unsigned char>)
class MathSolver final {
private:
	using value_type = T;

public:
	template<class Iter>
	explicit MathSolver(Iter begin, Iter end)
		: data_(std::distance(begin, end)), xyProductVector_(this->data_.capacity()),
	      xxProductVector_(this->data_.capacity()), yyProductVector_(this->data_.capacity()),
	      yCapVector_(this->data_.capacity()), yCapyTildeDiffVector_(this->data_.capacity()),
	      yCapyTildeDiffProductVector_(this->data_.capacity()), yCapyDiffVector_(this->data_.capacity()),
	      yCapyDiffProductVector_(this->data_.capacity()) {
		this->FillData(begin, end);

		this->CalculateProductXY();
		this->CalculateProductXX();
		this->CalculateProductYY();

		this->BuildModel();

		this->CalculateCapY();
		this->CalculateCapYTildeYDiff();
		this->CalculateCapYTildeYDiffProduct();
		this->CalculateCapYYDiff();
		this->CalculateCapYYDiffProduct();
	}

	//-------------------- VECTORS' GETTERS -----------------------------------//

	[[nodiscard]] std::vector<value_type> GetDataX() const {
		std::vector<value_type> result(this->data_.size());

		std::for_each(this->data_.cbegin(), this->data_.cend(),
			[i = 0, &result](const Point<value_type>& point) mutable  {
			result[i++] = point.x();
		}
		);

		return result;
	}

	[[nodiscard]] std::vector<value_type> GetDataY() const {
		std::vector<value_type> result(this->data_.size());

		std::for_each(this->data_.cbegin(), this->data_.cend(),
			[i = 0, &result](const Point<value_type>& point) mutable  {
			result[i++] = point.y();
		}
		);

		return result;
	}

	[[nodiscard]] std::vector<value_type> GetDataXXProduct() const {
		return this->xxProductVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataXYProduct() const {
		return this->xyProductVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYYProduct() const {
		return this->yyProductVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYCap() const {
		return this->yCapVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYCapYTildeDiff() const {
		return this->yCapyTildeDiffVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYCapYTildeDiffProduct() const {
		return this->yCapyTildeDiffProductVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYCapYDiff() const {
		return this->yCapyDiffVector_;
	}

	[[nodiscard]] std::vector<value_type> GetDataYCapYDiffProduct() const {
		return this->yCapyDiffProductVector_;
	}

	//-------------------- SUMS' GETTERS -------------------------------------//

	[[nodiscard]] value_type GetSumX() const {
		const auto xVector = this->GetDataX();
		return this->ReduceSum(xVector.cbegin(), xVector.cend());
	}

	[[nodiscard]] value_type GetSumY() const {
		const auto yVector = this->GetDataY();
		return this->ReduceSum(yVector.cbegin(), yVector.cend());
	}

	[[nodiscard]] value_type GetSumXXProduct() const {
		return this->ReduceSum(this->xxProductVector_.cbegin(), this->xxProductVector_.cend());
	}

	[[nodiscard]] value_type GetSumXYProduct() const {
		return this->ReduceSum(this->xyProductVector_.cbegin(), this->xyProductVector_.cend());
	}

	[[nodiscard]] value_type GetSumYYProduct() const {
		return this->ReduceSum(this->yyProductVector_.cbegin(), this->yyProductVector_.cend());
	}

	[[nodiscard]] value_type GetSumCapY() const {
		return this->ReduceSum(this->yCapVector_.cbegin(), this->yCapVector_.cend());
	}

	[[nodiscard]] value_type GetSumCapYTildeYDiff() const {
		return this->ReduceSum(this->yCapyTildeDiffVector_.cbegin(), this->yCapyTildeDiffVector_.cend());
	}

	[[nodiscard]] value_type GetSumCapYTildeYDiffProduct() const {
		return this->ReduceSum(this->yCapyTildeDiffProductVector_.cbegin(), this->yCapyTildeDiffProductVector_.cend());
	}

	[[nodiscard]] value_type GetSumCapYYDiff() const {
		return this->ReduceSum(this->yCapyDiffVector_.cbegin(), this->yCapyDiffVector_.cend());
	}

	[[nodiscard]] value_type GetSumCapYYDiffProduct() const {
		return this->ReduceSum(this->yCapyDiffProductVector_.cbegin(), this->yCapyDiffProductVector_.cend());
	}

	//-------------------- ANOTHER GETTERS -------------------------------------//

	[[nodiscard]] value_type GetXExpectedValue() const {
		auto x = this->GetDataX();
		return this->ReduceSum(x.cbegin(), x.cend()) / x.size();
	}

	[[nodiscard]] value_type GetYExpectedValue() const {
		auto y = this->GetDataY();
		return this->ReduceSum(y.cbegin(), y.cend()) / y.size();
	}

	//---------------------- MATH -----------------------------------------//

	[[nodiscard]] int GetK() const {
		return 1;
	}

	[[nodiscard]] value_type GetFStatistics() const {
		const auto k = this->GetK();

		const auto chisl = this->GetSumCapYTildeYDiffProduct() * (this->data_.size() - 2);
		const auto zname = this->GetSumCapYYDiffProduct() * k;

		return chisl / zname;
	}

private:
	std::vector<Point<value_type>> data_;

	std::vector<value_type> xyProductVector_;
	std::vector<value_type> xxProductVector_;
	std::vector<value_type> yyProductVector_;

	std::vector<value_type> yCapVector_;
	std::vector<value_type> yCapyTildeDiffVector_;
	std::vector<value_type> yCapyTildeDiffProductVector_;
	std::vector<value_type> yCapyDiffVector_;
	std::vector<value_type> yCapyDiffProductVector_;

	std::function<value_type(value_type)> model_;

	template<class Iter>
	void FillData(Iter begin, Iter end) {
		this->ForEach(begin, end,
			[i = 0, this](const Point<value_type>& point) mutable  {
				this->data_[i++] = point;
			}
		);
	}

	void CalculateProductXY() {
		this->ForEach(this->data_.cbegin(), this->data_.cend(),
			[i = 0, this](const Point<value_type>& point) mutable  {
				this->xyProductVector_[i++] = point.x() * point.y();
			}
		);
	}

	void CalculateProductXX() {
		this->ForEach(this->data_.cbegin(), this->data_.cend(),
			[i = 0, this](const Point<value_type>& point) mutable  {
				this->xxProductVector_[i++] = point.x() * point.x();
			}
		);
	}

	void CalculateProductYY() {
		this->ForEach(this->data_.cbegin(), this->data_.cend(),
			[i = 0, this](const Point<value_type>& point) mutable  {
				this->yyProductVector_[i++] = point.y() * point.y();
			}
		);
	}

	void BuildModel() {
		auto alphaOne = this->data_.size() * this->GetSumXYProduct() - this->GetSumX() * this->GetSumY();
		alphaOne /= this->data_.size() * this->GetSumXXProduct() - std::pow(this->GetSumX(), 2.0);

		auto alphaZero = (this->GetSumY() - alphaOne * this->GetSumX()) / this->data_.size();

		this->model_ = [alphaOne, alphaZero](value_type x) {
			return alphaOne * x + alphaZero;
		};
	}

	void CalculateCapY() {
		this->ForEach(this->data_.cbegin(), this->data_.cend(),
			[i = 0, this](const Point<value_type>& point) mutable {
				this->yCapVector_[i++] = this->model_(point.x());
			}
		);
	}

	void CalculateCapYTildeYDiff() {
		this->ForEach(this->yCapVector_.cbegin(), this->yCapVector_.cend(),
			[i = 0, this](const double y) mutable {
				this->yCapyTildeDiffVector_[i++] = y - this->GetYExpectedValue();
			}
		);
	}

	void CalculateCapYTildeYDiffProduct() {
		this->ForEach(this->yCapyTildeDiffVector_.cbegin(), this->yCapyTildeDiffVector_.cend(),
			[i = 0, this](const double y) mutable {
				this->yCapyTildeDiffProductVector_[i++] = std::pow(y, 2.0);
			}
		);
	}

	void CalculateCapYYDiff() {
		this->ForEach(this->data_.cbegin(), this->data_.cend(),
			[i = 0, this](const Point<value_type>& point) mutable {
				this->yCapyDiffVector_[i] = this->yCapVector_[i] - point.y();
				++i;
			}
		);
	}

	void CalculateCapYYDiffProduct() {
		this->ForEach(this->yCapyDiffVector_.cbegin(), this->yCapyDiffVector_.cend(),
			[i = 0, this](const double y) mutable {
				this->yCapyDiffProductVector_[i++] = std::pow(y, 2.0);
			}
		);
	}

	template<class Iter, class Func>
	void ForEach(Iter begin, Iter end, Func func) {
		if (this->data_.empty()) {
			return;
		}

		std::for_each(begin, end, func);
	}

	template<class Iter>
	[[nodiscard]] value_type ReduceSum(Iter begin, Iter end) const {
		return std::reduce(begin, end, value_type{ 0.0 }, std::plus());
	}
};
