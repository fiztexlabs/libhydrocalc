#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <string.h>

LRESULT getType_impl(
	MCSTRING* const _result,
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
		std::string type = hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()->getType();

		_result->str = MathcadAllocate(type.length() + 1);
		if (_result->str == NULL)
		{
			return MAKELRESULT(12, 0);
		}

		strcpy_s(_result->str, type.length() + 1, type.c_str());
	}
	catch (const std::exception& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	return 0;
}

FUNCTIONINFO fi_getType =
{
	"hr_getType",
	"",
	"",
	(LPCFUNCTION)getType_impl,
	STRING,
	1,
	{COMPLEX_SCALAR}
};