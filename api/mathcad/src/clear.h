#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

// Function used for clear all hydraulic resistances in the worksheet

LRESULT clear_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _plug)
{
	hydrocalc::mathcad::hr_vec.clear();

	_result->real = 0.0;
	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_clear =
{
	"hr_clear",
	"",
	"",
	(LPCFUNCTION)clear_impl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};