#include <pch.h>
#include <HydraulicResistances/IBaseHydraulicResistance.h>
#include <HydraulicResistances/CylindricalFriction.h>
#include <HydraulicResistances/RingFriction.h>
#include <HydraulicResistances/CylindricalBend.h>
#include <HydraulicResistances/StraightCylindricalDiffuser.h>
#include <HydraulicResistances/CurveCylindricalDiffuser.h>
#include <HydraulicResistances/StraightCylindricalConfuser.h>
#include <HydraulicResistances/CurveCylindricalConfuser.h>
#include <HydraulicResistances/HydraulicComposite.h>
#include <HydraulicResistances/CylindricalBendNiche.h>
#include <HydraulicResistances/SharpUnexpectedSizeChange.h>

__HSAPI  IBaseHydraulicResistance* __HSAPIENTRY CylindricalFrictionFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new CylindricalFriction(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY RingFrictionFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new RingFriction(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY CylindricalBendFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new CylindricalBend(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY CylindricalBendNicheFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new CylindricalBendNiche(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY StraightCylindricalDiffuserFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new StraightCylindricalDiffuser(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY StraightCylindricalConfuserFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new StraightCylindricalConfuser(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY CurveCylindricalDiffuserFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return  new CurveCylindricalDiffuser(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY CurveCylindricalConfuserFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new CurveCylindricalConfuser(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY SharpUnexpectedSizeChangeFab(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
{
	return new SharpUnexpectedSizeChange(name, Re, G);
}

__HSAPI IBaseHydraulicResistance* __HSAPIENTRY CompositeFab(const std::string& name, const std::vector<HSReal>& G, const std::vector<IBaseHydraulicResistance*>& ptrCompositeElements)
{
	return new HydraulicComposite(name, G, ptrCompositeElements);
}
