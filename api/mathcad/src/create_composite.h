#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

LRESULT createComposite_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _Re,
	const COMPLEXARRAY* const _G,
	const COMPLEXARRAY* const _elements,
	const MCSTRING* const _name,
	const COMPLEXSCALAR* const _vis,
	const COMPLEXSCALAR* const _unique)
{
	if ((static_cast<int>(_unique->real) != _unique->real) ||
		((static_cast<int>(_unique->real) != 0) && (static_cast<int>(_unique->real) != 1)))
	{
		return MAKELRESULT(6, 6);
	}


	std::vector<hydrocalc::HydraulicResistance*> els;
	try
	{
		for (size_t i = 0; i < _elements->rows; ++i)
		{
			if (static_cast<int>(_elements->hReal[0][i]) != _elements->hReal[0][i])
			{
				return MAKELRESULT(7, 3);
			}
			els.push_back(hydrocalc::mathcad::hr_vec.at(static_cast<int>(_elements->hReal[0][i])).get());
		}
	}
	catch (const std::exception & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(8, 3);
	}

	try
	{
		hydrocalc::mathcad::hr_vec.push_back(std::unique_ptr<hydrocalc::HydraulicResistance>(hydrocalc::createComposite(
			_Re->real,
			std::vector<hydrocalc::real>(*(_G->hReal), *(_G->hReal) + _G->rows),
			els,
			std::string(_name->str),
			_vis->real,
			_unique->real)));
	}
	catch (const hydrocalc::ExceptionGeometryOutOfRange & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const hydrocalc::ExceptionInvalidElementType & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(3, 1);
	}
	catch (const hydrocalc::ExceptionUnphysicalViscosity & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(5, 5);
	}
	catch (const hydrocalc::ExceptionInvalidValue & exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const std::exception & exec)
	{
		std::cerr << exec.what();

		if (_G->rows < 2)
		{
			return MAKELRESULT(2, 2);
		}
		else
		{
			return MAKELRESULT(8, 3);
		}
	}

	_result->real = static_cast<int>(hydrocalc::mathcad::hr_vec.size() - 1);
	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_createComposite =
{
	"hr_createComposite",
	"",
	"",
	(LPCFUNCTION)createComposite_impl,
	COMPLEX_SCALAR,
	6,
	{COMPLEX_SCALAR, COMPLEX_ARRAY, COMPLEX_ARRAY, STRING, COMPLEX_SCALAR, COMPLEX_SCALAR}
};