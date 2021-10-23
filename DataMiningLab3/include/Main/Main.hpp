#pragma once
#include "MainHeader.hpp"
#include "argparse/argparse.hpp"
#include "DataGetter/JsonDataGetter.hpp"
#include "FisherF/FisherF.hpp"

class Main {
private:
	static const std::pair <const char*, const char*> FILES_ARG_STR;

public:
	explicit Main(int argc, char* argv[]) {
		this->InitArgv(argc, argv);
	}

	int LaunchMain() {
		Main::SetLocale(1251u);

		try {
			this->ParseArgs();
		}
		catch (const std::exception&) {
			fmt::print(fmt::fg(fmt::color::orange),
				"ВНИМАНИЕ! Добавьте файлы с входными данными...\nПример: {} {} fileName.json\n",
				this->argv_.front(), Main::FILES_ARG_STR.second);

			return EXIT_FAILURE;
		}

		for (const auto& path : this->filePaths_) {
			fmt::print("Файл данных: ");
			fmt::print(fmt::fg(fmt::color::aqua), "{}\n", path);

			std::fstream file(path, std::fstream::in);

			if (!file.is_open()) {
				throw std::runtime_error("Wrong path or file doesn't exist!");
			}

			const std::unique_ptr<IDataGetter> dataGetter
				= std::make_unique<JsonDataGetter>(std::move(file));

			const auto points = dataGetter->GetData();
			const auto probability = dataGetter->GetConfidenceProbability();

			const std::unique_ptr<MathSolver<double>> mathSolver{
				new MathSolver<double>{ points.begin(), points.end() }
			};

			const auto table = this->CreateTable(mathSolver.get());
			std::cout << table << '\n';

			Main::PrintDelimiter(std::cout, '=', 60u);

			std::cout << std::format("Математическое ожидание x: {:.4f}\n", mathSolver->GetXExpectedValue());
			std::cout << std::format("Математическое ожидание y: {:.4f}\n", mathSolver->GetYExpectedValue());

			Main::PrintDelimiter(std::cout, '=', 60u);

			std::cout << std::format("F статистика: {:.4f}\n", mathSolver->GetFStatistics());

			Main::PrintDelimiter(std::cout, '=', 60u);

			const auto modelF = mathSolver->GetFStatistics();
			const auto fisherF = std::make_unique<FisherF>(mathSolver->GetK(), mathSolver->GetDataX().size() - 2)
				->GetFStatistics(1.0 - probability);

			if (modelF < fisherF) {
				std::cout << std::format("{:.4f} < {:.4f}", modelF, fisherF) << '\n';
				std::cout << "Модель неадекватна" << '\n';
			}
			else {
				std::cout << std::format("{:.4f} >= {:.4f}", modelF, fisherF) << '\n';
				std::cout << "Модель адекватна" << '\n';
			}

			Main::PrintDelimiter(std::cout, '=', 60u);
			std::cout << std::flush;
		}

		return EXIT_SUCCESS;
	}

private:
	std::vector<std::string> argv_;
	std::vector<std::string> filePaths_;

	void InitArgv(int argc, char* argv[]) {
		std::copy_n(argv, argc, std::back_inserter(this->argv_));
	}

	void ParseArgs() {
		try {
			const auto argumentParser = std::make_unique<argparse::ArgumentParser>();
			argumentParser->add_argument(Main::FILES_ARG_STR.first, Main::FILES_ARG_STR.second)
				.required()
				.nargs(static_cast<int>(this->argv_.size()) - 2)
				.help("specify the input JSON-files.");

			argumentParser->parse_args(this->argv_);

			this->filePaths_ = argumentParser->get<std::vector<std::string>>(Main::FILES_ARG_STR.first);
		}
		catch (const std::exception&) {
			throw;
		}
	}

	template<class T>
	[[nodiscard]] tabulate::Table CreateTable(MathSolver<T>* mathSolver) const {
		tabulate::Table table;

		table.add_row({
				"N", "X_i", "Y_i",
				"X_i * Y_i", "X_i^^2",
				"Y_i^^2", "^y_i", "^y_i - ~y",
				"(^y_i - ~y)^^2", "^y_i - y_i",
				"(^y_i - y_i)^^2"
			}
		);

		const auto x = mathSolver->GetDataX();
		const auto y = mathSolver->GetDataY();

		const auto xxProduct = mathSolver->GetDataXXProduct();
		const auto xyProduct = mathSolver->GetDataXYProduct();
		const auto yyProduct = mathSolver->GetDataYYProduct();

		const auto yCap           = mathSolver->GetDataYCap();

		const auto yCapyTildeDiff = mathSolver->GetDataYCapYTildeDiff();
		const auto yCapyTildeDiffProduct = mathSolver->GetDataYCapYTildeDiffProduct();

		const auto yCapyDiff = mathSolver->GetDataYCapYDiff();
		const auto yCapyDiffProduct = mathSolver->GetDataYCapYDiffProduct();

		const auto size = x.size();

		for (auto i = 0u; i < size; ++i) {
			table.add_row({
					std::format("{}", i + 1),
					std::format("{:.4f}", x.at(i)),
					std::format("{:.4f}", y.at(i)),
					std::format("{:.4f}", xyProduct.at(i)),
					std::format("{:.4f}", xxProduct.at(i)),
					std::format("{:.4f}", yyProduct.at(i)),
					std::format("{:.4f}", yCap.at(i)),
					std::format("{:.4f}", yCapyTildeDiff.at(i)),
					std::format("{:.4f}", yCapyTildeDiffProduct.at(i)),
					std::format("{:.4f}", yCapyDiff.at(i)),
					std::format("{:.4f}", yCapyDiffProduct.at(i))
				}
			);
		}
		table.add_row( {
				std::format("sum:"),
				std::format("{:.4f}", mathSolver->GetSumX()),
				std::format("{:.4f}", mathSolver->GetSumY()),
				std::format("{:.4f}", mathSolver->GetSumXYProduct()),
				std::format("{:.4f}", mathSolver->GetSumXXProduct()),
				std::format("{:.4f}", mathSolver->GetSumYYProduct()),
				std::format("{:.4f}", mathSolver->GetSumCapY()),
				std::format("{:.4f}", mathSolver->GetSumCapYTildeYDiff()),
				std::format("{:.4f}", mathSolver->GetSumCapYTildeYDiffProduct()),
				std::format("{:.4f}", mathSolver->GetSumCapYYDiff()),
				std::format("{:.4f}", mathSolver->GetSumCapYYDiffProduct())
			}
		);

		return table;
	}

	static void SetLocale(unsigned code) {
		#if defined(WIN32)
				SetConsoleCP(code);
				SetConsoleOutputCP(code);
		#endif
	}

	static void PrintDelimiter(std::ostream& out, const char symbol = '-', const size_t count = 40u) {
		out << std::string(count, symbol) << '\n';
	}
};

const std::pair <const char*, const char*> Main::FILES_ARG_STR = { "-f", "--files" };
