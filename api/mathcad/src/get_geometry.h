#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

LRESULT getGeometry_impl(
	COMPLEXARRAY* const _result,
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
		std::vector<hydrocalc::real> G;

		hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()->getGeometry(G);

		// allocate memory
		_result->cols = 1;
		_result->rows = G.size();

		if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
		{
			return MAKELRESULT(12, 0);
		}
		for (size_t i = 0; i < G.size(); ++i)
		{
			_result->hReal[0][i] = G.at(i);
		}

	}
	catch (const std::exception& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	return 0;
}

FUNCTIONINFO fi_getGeometry =
{
	"hr_getGeometry",
	"",
	"",
	(LPCFUNCTION)getGeometry_impl,
	COMPLEX_ARRAY,
	1,
	{COMPLEX_SCALAR}
};