#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <libhydrocalc/composite.h>

LRESULT composite_erase_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _id,
	const COMPLEXSCALAR* const _id_to_erase)
{
	if (static_cast<int>(_id->real) != _id->real)
	{
		return MAKELRESULT(7, 1);
	}
	if (static_cast<int>(_id->imag) != 0)
	{
		return MAKELRESULT(1, 1);
	}

	if (static_cast<int>(_id_to_erase->real) != _id_to_erase->real)
	{
		return MAKELRESULT(7, 2);
	}
	if (static_cast<int>(_id_to_erase->imag) != 0)
	{
		return MAKELRESULT(1, 2);
	}

	try
	{
		static_cast<hydrocalc::Composite*>(hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get())->erase(
			hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id_to_erase->real)).get()
		);
	}
	catch (const hydrocalc::ExceptionInvalidElementId& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(13, 2);
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

FUNCTIONINFO fi_composite_erase =
{
	"hr_composite_erase",
	"",
	"",
	(LPCFUNCTION)composite_erase_impl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};