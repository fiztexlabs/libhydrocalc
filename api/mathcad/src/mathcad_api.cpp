#include <MCADINCL.H>
#include <libhydrocalc/hydrocalc.h>
#include <math.h>
#include <windows.h>
#include <SDKDDKVer.h>
#include <vector>
#include <memory>
#include <string>
#include <libhydrocalc/exceptions.h>
#include <exception>
#include <iostream>

namespace hydrocalc::mathcad
{
	std::vector<std::unique_ptr<hydrocalc::HydraulicResistance>> hr_vec;
}

char* HydrocalcFunctionErrors[8] =
{
  "Value must be real",
  "Not enougth geometry parameters",
  "Incorrect element type",
  "Incorrect element geometry",
  "Incorrect viscosity",
  "Value must be boolean",
  "Element id must be integer",
  "Incorrect element id"
};

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
	catch (const hydrocalc::ExceptionGeometryOutOfRange& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const hydrocalc::ExceptionInvalidElementType& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(3, 1);
	}
	catch (const hydrocalc::ExceptionUnphysicalViscosity& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(5, 5);
	}
	catch (const hydrocalc::ExceptionInvalidValue& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const std::exception& exec)
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
	"createHydraulicResistance",
	"",
	"",
	(LPCFUNCTION)createHydraulicResistance_impl,
	COMPLEX_SCALAR,
	5,
	{STRING, COMPLEX_SCALAR, COMPLEX_ARRAY, STRING, COMPLEX_SCALAR}
};




LRESULT createComposite_impl(
	COMPLEXSCALAR* const _result,
	const COMPLEXSCALAR* const _Re,
	const COMPLEXARRAY* const _G,
	const COMPLEXARRAY* const _elements,
	const MCSTRING* const _name,
	const COMPLEXSCALAR* const _vis,
	const COMPLEXSCALAR* const _unique)
{
	/*for(size_t i = 0; i < _G->rows; ++i)
	{
		if (_G->hImag[0][0] != NULL)
		{
			return MAKELRESULT(1, 3);
		}
	}*/

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
	catch (const std::exception& exec)
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
	catch (const hydrocalc::ExceptionGeometryOutOfRange& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const hydrocalc::ExceptionInvalidElementType& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(3, 1);
	}
	catch (const hydrocalc::ExceptionUnphysicalViscosity& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(5, 5);
	}
	catch (const hydrocalc::ExceptionInvalidValue& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(4, 3);
	}
	catch (const std::exception& exec)
	{
		std::cerr << exec.what();

		return MAKELRESULT(2, 3);
	}

	//_result->real = static_cast<int>(hydrocalc::mathcad::hr_vec.size() - 1);
	_result->real = _G->rows;
	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO fi_createComposite =
{
	"createComposite",
	"",
	"",
	(LPCFUNCTION)createComposite_impl,
	COMPLEX_SCALAR,
	6,
	{COMPLEX_SCALAR, COMPLEX_ARRAY, COMPLEX_ARRAY, STRING, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (CreateUserErrorMessageTable(hModule, 8, HydrocalcFunctionErrors))
		{
			// SOURCE
			CreateUserFunction(hModule, &fi_createHydraulicResistance);
			CreateUserFunction(hModule, &fi_createComposite);
		};

		break;
	}
	default:
	{
		break;
	}
	}
	return TRUE;
}
