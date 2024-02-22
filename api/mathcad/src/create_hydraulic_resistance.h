#pragma once
#include <src/mathcad_api.h>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/exceptions.h>

LRESULT createHydraulicResistance_impl(
	COMPLEXSCALAR* const _result,
	const MCSTRING* const _type,
	const COMPLEXSCALAR* const _Re,
	const COMPLEXARRAY* const _G,
	const MCSTRING* const _name,
	const COMPLEXSCALAR* const _vis)
{
	/*for(size_t i = 0; i < _G->rows; ++i)
	{
		if (_G->hImag[0][0] != NULL)
		{
			return MAKELRESULT(1, 3);
		}
	}*/

	try
	{
		hydrocalc::mathcad::hr_vec.push_back(std::unique_ptr<hydrocalc::HydraulicResistance>(hydrocalc::createHydraulicResistance(
			std::string(_type->str),
			_Re->real,
			std::vector<hydrocalc::real>(*(_G->hReal), *(_G->hReal) + _G->rows),
			std::string(_name->str),
			_vis->real)));
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

		return MAKELRESULT(2, 3);
	}

	_result->real = static_cast<int>(hydrocalc::mathcad::hr_vec.size() - 1);
	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_createHydraulicResistance =
{
	"hr_createHydraulicResistance",
	"",
	"",
	(LPCFUNCTION)createHydraulicResistance_impl,
	COMPLEX_SCALAR,
	5,
	{STRING, COMPLEX_SCALAR, COMPLEX_ARRAY, STRING, COMPLEX_SCALAR}
};