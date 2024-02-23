#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <libhydrocalc/composite.h>

LRESULT composite_get_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _id,
	const COMPLEXSCALAR* const _id_to_get)
{
	if (static_cast<int>(_id->real) != _id->real)
	{
		return MAKELRESULT(7, 1);
	}
	if (static_cast<int>(_id->imag) != 0)
	{
		return MAKELRESULT(1, 1);
	}

	if (static_cast<int>(_id_to_get->real) != _id_to_get->real)
	{
		return MAKELRESULT(7, 2);
	}
	if (static_cast<int>(_id_to_get->imag) != 0)
	{
		return MAKELRESULT(1, 2);
	}

	try
	{
		auto composite{ static_cast<hydrocalc::Composite*>(hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()) };

		hydrocalc::HydraulicResistance* element(composite->get(static_cast<size_t>(_id_to_get->real)));

		if (composite->isUnique())
		{
			// put copy of internal object
			hydrocalc::mathcad::hr_vec.push_back(std::unique_ptr<hydrocalc::HydraulicResistance>(composite->get(static_cast<size_t>(_id_to_get->real), 1)));
			_result->real = static_cast<int>(hydrocalc::mathcad::hr_vec.size() - 1);
		}
		else
		{
			_result->real = static_cast<int>(std::distance(
				hydrocalc::mathcad::hr_vec.begin(),
				std::find_if(
					hydrocalc::mathcad::hr_vec.begin(),
					hydrocalc::mathcad::hr_vec.end(),
					[element](const std::unique_ptr<hydrocalc::HydraulicResistance>& hr) { return hr.get() == element ? 1 : 0; }
				)
			));
		}
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

FUNCTIONINFO fi_composite_get =
{
	"hr_composite_get",
	"",
	"",
	(LPCFUNCTION)composite_get_impl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};