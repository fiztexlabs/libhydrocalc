#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

LRESULT getCrossSectionArea_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _id)
{
	if (static_cast<int>(_id->real) != _id->real)
	{
		return MAKELRESULT(7, 1);
	}
	if (static_cast<int>(_id->imag) != 0)
	{
		return MAKELRESULT(1, 1);
	}

	try
	{
		_result->real = hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()->getCrossSectionArea();
	}
	catch (const std::exception & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_getCrossSectionArea =
{
	"hr_getCrossSectionArea",
	"",
	"",
	(LPCFUNCTION)getCrossSectionArea_impl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};