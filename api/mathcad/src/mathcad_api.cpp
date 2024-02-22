#include <src/mathcad_api.h>
#include <src/create_hydraulic_resistance.h>
#include <src/create_composite.h>
#include <src/evaluate.h>
#include <src/get_local_resistance_coeff.h>
#include <src/get_cross_section_area.h>
#include <src/get_diagram.h>
#include <src/get_name.h>
#include <src/get_friction_part_coeff.h>

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (CreateUserErrorMessageTable(hModule, ERR_NUM, HydrocalcFunctionErrors))
		{
			// SOURCE
			CreateUserFunction(hModule, &fi_createHydraulicResistance);
			CreateUserFunction(hModule, &fi_createComposite);
			CreateUserFunction(hModule, &fi_evaluate);
			CreateUserFunction(hModule, &fi_getLocalResistanceCoeff);
			CreateUserFunction(hModule, &fi_getCrossSectionArea);
			CreateUserFunction(hModule, &fi_getDiagram);
			CreateUserFunction(hModule, &fi_getName);
			CreateUserFunction(hModule, &fi_getFrictionPartCoeff);
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
