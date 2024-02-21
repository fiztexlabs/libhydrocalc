#include <MCADINCL.H>
#include <libhydrocalc/c/c_api.h>
#include <math.h>
#include <windows.h>
#include <SDKDDKVer.h>
#include <vector>

std::vector<int> i;

char* HydrocalcFunctionErrors[4] =
{
  "Value must be real",
  "Value must be positive",
  "Value must be integer",
  "Not enougth memory"
};

LRESULT createHydraulicResistance_impl(
	COMPLEXSCALAR* const _result,
	const MCSTRING* const _type,
	const COMPLEXSCALAR* const _Re,
	const COMPLEXARRAY* const _G,
	const MCSTRING* const _name,
	const COMPLEXSCALAR* const _vis)
{
	//if (_Id->imag != 0.0)
	//{
	//	return MAKELRESULT(1, 1);
	//}

	//if (_Id->real < 0.0)
	//{
	//	return MAKELRESULT(2, 1);
	//}

	//if (static_cast<int>(_Id->real) != _Id->real)
	//{
	//	return MAKELRESULT(3, 1);
	//}

	//if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	//{
	//	return MAKELRESULT(4, 1);
	//}
	//else
	//{
	//	hr_vec.push_back(std::unique_ptr<HydraulicResistance>(createHydraulicResistance(SubstanceName)));

	//	return static_cast<int>(SubstVector.size() - 1);
	//	//_result->real = rgpTCRIT(static_cast<const int>(_Id->real));
	//}

	//hr_vec.push_back(std::unique_ptr<HydraulicResistance>(createHydraulicResistance(
	//	std::string(_type->str), 
	//	_Re->real, 
	//	std::vector<real>(*(_G->hReal), *(_G->hReal)+_G->rows),
	//	std::string(_name->str),
	//	_vis->real)));
	////hr_vec.push_back(std::unique_ptr<HydraulicResistance>(createHydraulicResistance(std::string(_type->str))));


	_result->real = createHydraulicResistance(
		_type->str,
		_Re->real,
		*(_G->hReal),
		_G->rows,
		_name->str,
		_vis->real
	);

	_result->real = 100.0;
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


//LRESULT createHydraulicResistance_impl(
//	COMPLEXSCALAR* const _result,
//	const COMPLEXSCALAR* const _Re)
//{
//	_result->real = _Re->real;
//
//	_result->imag = 0.0;
//
//	return 0;
//}
//
//FUNCTIONINFO fi_createHydraulicResistance =
//{
//	"abc",
//	"",
//	"",
//	(LPCFUNCTION)createHydraulicResistance_impl,
//	COMPLEX_SCALAR,
//	1,
//	{COMPLEX_SCALAR}
//};

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (CreateUserErrorMessageTable(hModule, 4, HydrocalcFunctionErrors))
		{
			// SOURCE
			CreateUserFunction(hModule, &fi_createHydraulicResistance);
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
