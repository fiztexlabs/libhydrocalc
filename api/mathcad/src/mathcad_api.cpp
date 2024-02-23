#include <src/mathcad_api.h>
#include <src/delete.h>
#include <src/clear.h>
#include <src/create_hydraulic_resistance.h>
#include <src/create_composite.h>
#include <src/evaluate.h>
#include <src/get_cross_section_area.h>
#include <src/get_diagram.h>
#include <src/get_friction_part_coeff.h>
#include <src/get_hydraulic_diameter.h>
#include <src/get_geometry.h>
#include <src/get_geometry_part_coeff.h>
#include <src/get_id.h>
#include <src/get_length.h>
#include <src/get_local_resistance_coeff.h>
#include <src/get_name.h>
#include <src/get_re.h>
#include <src/get_rel_friction_coeff.h>
#include <src/get_rou.h>
#include <src/get_type.h>
#include <src/get_viscosity.h>
#include <src/set_geometry.h>
#include <src/set_length.h>
#include <src/set_name.h>
#include <src/set_re.h>
#include <src/set_rou.h>
#include <src/set_viscosity.h>
#include <src/composite_erase.h>
#include <src/composite_get.h>
#include <src/composite_getall.h>
#include <src/composite_pushback.h>
#include <src/composite_size.h>

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (CreateUserErrorMessageTable(hModule, ERR_NUM, HydrocalcFunctionErrors))
		{
			CreateUserFunction(hModule, &fi_clear);

			CreateUserFunction(hModule, &fi_createHydraulicResistance);
			CreateUserFunction(hModule, &fi_createComposite);
			CreateUserFunction(hModule, &fi_evaluate);
			CreateUserFunction(hModule, &fi_getLocalResistanceCoeff);
			CreateUserFunction(hModule, &fi_getCrossSectionArea);
			CreateUserFunction(hModule, &fi_getDiagram);
			CreateUserFunction(hModule, &fi_getName);
			CreateUserFunction(hModule, &fi_getFrictionPartCoeff);
			CreateUserFunction(hModule, &fi_getHydraulicDiameter);
			CreateUserFunction(hModule, &fi_getGeometry);
			CreateUserFunction(hModule, &fi_getGeometryPartCoeff);
			CreateUserFunction(hModule, &fi_getId);
			CreateUserFunction(hModule, &fi_getLength);
			CreateUserFunction(hModule, &fi_getRe);
			CreateUserFunction(hModule, &fi_getRelFrictionCoeff);
			CreateUserFunction(hModule, &fi_getRou);
			CreateUserFunction(hModule, &fi_getType);
			CreateUserFunction(hModule, &fi_getViscosity);
			CreateUserFunction(hModule, &fi_setGeometry);
			CreateUserFunction(hModule, &fi_setLength);
			CreateUserFunction(hModule, &fi_setRe);
			CreateUserFunction(hModule, &fi_setRou);
			CreateUserFunction(hModule, &fi_setViscosity);
			CreateUserFunction(hModule, &fi_setName);
			CreateUserFunction(hModule, &fi_delete);

			// Composite
			CreateUserFunction(hModule, &fi_composite_erase);
			CreateUserFunction(hModule, &fi_composite_get);
			CreateUserFunction(hModule, &fi_composite_getAll);
			CreateUserFunction(hModule, &fi_composite_push_back);
			CreateUserFunction(hModule, &fi_composite_size);
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
