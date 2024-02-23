#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>
#include <libhydrocalc/composite.h>

LRESULT composite_getAll_impl(
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
		auto composite{ static_cast<hydrocalc::Composite*>(hydrocalc::mathcad::hr_vec.at(static_cast<size_t>(_id->real)).get()) };

		std::vector<hydrocalc::HydraulicResistance*> in_elements;

		composite->get(in_elements, 1);

		// allocate memory
		_result->cols = 1;
		_result->rows = in_elements.size();

		if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
		{
			return MAKELRESULT(12, 0);
		}

		size_t i = 0;
		if (composite->isUnique())
		{
			for (auto hr : in_elements)
			{
				// put copy of internal object
				hydrocalc::mathcad::hr_vec.push_back(std::unique_ptr<hydrocalc::HydraulicResistance>(hr));

				_result->hReal[0][i] = static_cast<int>(hydrocalc::mathcad::hr_vec.size() - 1);
				++i;
			}
		}
		else
		{
			for (auto hr : in_elements)
			{
				_result->hReal[0][i] = static_cast<int>(std::distance(
					hydrocalc::mathcad::hr_vec.begin(),
					std::find_if(
						hydrocalc::mathcad::hr_vec.begin(),
						hydrocalc::mathcad::hr_vec.end(),
						[hr](const std::unique_ptr<hydrocalc::HydraulicResistance>& hr_f) { return hr_f.get() == hr ? 1 : 0; }
					)
				));
				++i;
			}
		}

	}
	catch (const std::exception& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 1);
	}

	return 0;
}

FUNCTIONINFO fi_composite_getAll =
{
	"hr_composite_getAll",
	"",
	"",
	(LPCFUNCTION)composite_getAll_impl,
	COMPLEX_ARRAY,
	1,
	{COMPLEX_SCALAR}
};