#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <string.h>

LRESULT getName_impl(
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
		std::string name;
		hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()->getName(name);

		_result->str = MathcadAllocate(name.length() + 1);
		if (_result->str == NULL)
		{
			return MAKELRESULT(12, 0);
		}

		strcpy_s(_result->str, name.length()+1, name.c_str());
	}
	catch (const std::exception & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	return 0;
}

FUNCTIONINFO fi_getName =
{
	"hr_getName",
	"",
	"",
	(LPCFUNCTION)getName_impl,
	STRING,
	1,
	{COMPLEX_SCALAR}
};