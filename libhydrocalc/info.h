#pragma once
#include <map>
#include <vector>
#include <string>
#include <libhydrocalc/settings.h>
#include <libhydrocalc/cylindrical_bend.h>
#include <functional>

namespace hydrocalc::info
{
	/**
	* @defgroup Info Service information
	* @{
	* @brief Service information about hydraulic resistance elements
	*/

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
		"CylindricalDiffuserStraight",
		"HydraulicResistanceDefined"
	};

	/**
	* @}
	*/

}