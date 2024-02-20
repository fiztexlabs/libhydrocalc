#pragma once
#include <map>
#include <vector>
#include <string>
#include <libhydrocalc/settings.h>
#include <libhydrocalc/cylindrical_bend.h>
#include <functional>

namespace hydrocalc::info
{
	inline const std::vector<std::string> elementsTypes
	{
		"CylindricalFriction",
		"RingFriction",
		"SharpUnexpectedSizeChange",
		"CylindricalBend",
		"CylindricalBendNiche",
		"CylindricalConfuserCurve",
		"CylindricalConfuserStraight",
		"CylindricalDiffuserCurve",
		"CylindricalDiffuserStraight"
	};

}