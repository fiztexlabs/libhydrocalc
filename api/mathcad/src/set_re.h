#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

LRESULT setRe_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _id,
	const COMPLEXSCALAR* const _Re)
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
		hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()->setRe(static_cast<hydrocalc::real>(_Re->real));
	}
	catch (const std::exception& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	_result->real = 0.0;
	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_setRe =
{
	"hr_setRe",
	"",
	"",
	(LPCFUNCTION)setRe_impl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};