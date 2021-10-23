#pragma once

#include <iostream>
#include <format>

#include <vector>

#if defined(WIN32)
	#include <Windows.h>
#endif

#include <fmt/color.h>

#include "tabulate/table.hpp"

#include "DataGetter/TestDataGetter.hpp"
#include "MathSolver/MathSolver.hpp"
