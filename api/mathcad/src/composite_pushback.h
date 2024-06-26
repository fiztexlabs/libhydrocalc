#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <libhydrocalc/composite.h>

LRESULT composite_push_back_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _id,
	const COMPLEXSCALAR* const _id_to_push_back)
{
	if (static_cast<int>(_id->real) != _id->real)
	{
		return MAKELRESULT(7, 1);
	}
	if (static_cast<int>(_id->imag) != 0)
	{
		return MAKELRESULT(1, 1);
	}

	if (static_cast<int>(_id_to_push_back->real) != _id_to_push_back->real)
	{
		return MAKELRESULT(7, 2);
	}
	if (static_cast<int>(_id_to_push_back->imag) != 0)
	{
		return MAKELRESULT(1, 2);
	}

	// check, that element is composite
	std::string type = hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real))->getType();
	if (type != "[Composite]")
	{
		return MAKELRESULT(14, 1);
	}

	try
	{
		dynamic_cast<hydrocalc::Composite*>(hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get())->push_back(
			hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id_to_push_back->real)).get()
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

FUNCTIONINFO fi_composite_push_back =
{
	"hr_composite_push_back",
	"",
	"",
	(LPCFUNCTION)composite_push_back_impl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};