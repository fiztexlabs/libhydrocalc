#pragma once
#include <libhydrocalc/settings.h>
#include <string>
#include <iostream>
#include <functional>

namespace hydrocalc
{
	/**
	* @brief Function calculate value of F approximation model depends on arg1 and arg2
	* @details Function used for calculate values with approx models
	* @param out[out]: Vector of outputs
	*/
	void approxModel(
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
	);
}
