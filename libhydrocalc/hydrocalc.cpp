#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/info.h>
#include <libhydrocalc/cylindrical_friction.h>
#include <libhydrocalc/ring_friction.h>
#include <libhydrocalc/sharp_unexpected_size_change.h>
#include <libhydrocalc/cylindrical_bend.h>
#include <libhydrocalc/cylindrical_bend_niche.h>
#include <libhydrocalc/cylindrical_confuser_curve.h>
#include <libhydrocalc/cylindrical_confuser_straight.h>
#include <libhydrocalc/cylindrical_diffuser_curve.h>
#include <libhydrocalc/cylindrical_diffuser_straight.h>
#include <libhydrocalc/composite.h>
#include <libhydrocalc/hydraulic_resistance_defined.h>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace hydrocalc;

HydraulicResistance* hydrocalc::createHydraulicResistance(
	const std::string& type, 
	const real Re, 
	const std::vector<real>& G, 
	const std::string& name,
	const real vis)
{
	if (type == "CylindricalFriction")
	{
		return new CylindricalFriction(Re, G, name, vis);
	}
	if (type == "RingFriction")
	{
		return new RingFriction(Re, G, name, vis);
	}
	if (type == "SharpUnexpectedSizeChange")
	{
		return new SharpUnexpectedSizeChange(Re, G, name, vis);
	}
	if (type == "CylindricalBend")
	{
		return new CylindricalBend(Re, G, name, vis);
	}
	if (type == "CylindricalBendNiche")
	{
		return new CylindricalBendNiche(Re, G, name, vis);
	}
	if (type == "CylindricalConfuserCurve")
	{
		return new CylindricalConfuserCurve(Re, G, name, vis);
	}
	if (type == "CylindricalConfuserStraight")
	{
		return new CylindricalConfuserStraight(Re, G, name, vis);
	}
	if (type == "CylindricalDiffuserCurve")
	{
		return new CylindricalDiffuserCurve(Re, G, name, vis);
	}
	if (type == "CylindricalDiffuserStraight")
	{
		return new CylindricalDiffuserStraight(Re, G, name, vis);
	}
	if (type == "HydraulicResistanceDefined")
	{
		return new HydraulicResistanceDefined(Re, G, name, vis);
	}
	
	// if user-defined element type incorrect, determine most likely correct element type
	std::vector<size_t> distances;
	for (size_t i = 0; i < info::elementsTypes.size(); ++i)
	{
		std::deque<bool> tmp(info::elementsTypes[i].size());
		for (size_t j = 0; j < std::min(tmp.size(), type.size()); ++j)
			tmp[j] = static_cast<char>(info::elementsTypes[i][j] == type[j]);
		auto distance = std::count(std::begin(tmp), std::end(tmp), true);
		distances.push_back(distance);
	}
	auto idx = std::distance(std::begin(distances), std::max_element(std::begin(distances), std::end(distances)));
	auto result = info::elementsTypes[idx];

	std::cerr << "%%err Invalid element type in function ""createHydraulicResistance"": " + type << "\n"
		"Element with the same name: " << result << std::endl;
	throw(ExceptionInvalidElementType("Invalid element type in function ""createHydraulicResistance"""));

	return nullptr;
}

HydraulicResistance* hydrocalc::createHydraulicResistance(const std::string& type)
{
	if (type == "CylindricalFriction")
	{
		return new CylindricalFriction();
	}
	if (type == "RingFriction")
	{
		return new RingFriction();
	}
	if (type == "SharpUnexpectedSizeChange")
	{
		return new SharpUnexpectedSizeChange();
	}
	if (type == "CylindricalBend")
	{
		return new CylindricalBend();
	}
	if (type == "CylindricalBendNiche")
	{
		return new CylindricalBendNiche();
	}
	if (type == "CylindricalConfuserCurve")
	{
		return new CylindricalConfuserCurve();
	}
	if (type == "CylindricalConfuserStraight")
	{
		return new CylindricalConfuserStraight();
	}
	if (type == "CylindricalDiffuserCurve")
	{
		return new CylindricalDiffuserCurve();
	}
	if (type == "CylindricalDiffuserStraight")
	{
		return new CylindricalDiffuserStraight();
	}

	// if user-defined element type incorrect, determine most likely correct element type
	std::vector<size_t> distances;
	for (size_t i = 0; i < info::elementsTypes.size(); ++i)
	{
		std::deque<bool> tmp(info::elementsTypes[i].size());
		for (size_t j = 0; j < std::min(tmp.size(), type.size()); ++j)
			tmp[j] = static_cast<char>(info::elementsTypes[i][j] == type[j]);
		auto distance = std::count(std::begin(tmp), std::end(tmp), true);
		distances.push_back(distance);
	}
	auto idx = std::distance(std::begin(distances), std::max_element(std::begin(distances), std::end(distances)));
	auto result = info::elementsTypes[idx];

	std::cerr << "%%err Invalid element type in function ""createHydraulicResistance"": " + type << "\n"
		"Element with the same name: " << result << std::endl;
	throw(ExceptionInvalidElementType("Invalid element type in function ""createHydraulicResistance"""));

	return nullptr;
}

HydraulicResistance* hydrocalc::createComposite(
	const real Re, 
	const std::vector<real>& G, 
	const std::vector<HydraulicResistance*>& elements, 
	const std::string& name, 
	const real vis, 
	bool unique)
{
	return new Composite(
		Re,
		G,
		elements,
		name,
		vis,
		unique
	);
}

HydraulicResistance* hydrocalc::createComposite()
{
	return new Composite();
}
