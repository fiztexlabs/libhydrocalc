#include <libhydrocalc/service.h>
#include <libhydrocalc/exceptions.h>
#include <limits>
#include <iostream>

using namespace hydrocalc;

void hydrocalc::approxModel(
	const real arg1,
	const real arg2,
	const std::function<void(
		const double* input,
		const int inputInc,
		double* value,
		const int valueInc,
		double* grad,
		const int gradNextDF,
		const int gradNextDX
		)>& F,
	std::vector<real>& out
)
{
	double value[2] = { static_cast<double>(0.0), static_cast<double>(0.0) };
	double args[2] = { static_cast<double>(arg1), static_cast<double>(arg2) };

	F(args, 1, value, 1, NULL, 0, 0);

	out = std::vector<real>(value, value + 2);
}