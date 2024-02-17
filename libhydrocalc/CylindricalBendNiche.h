#pragma once
#include <HydraulicResistances/CylindricalBend.h>

/**
* @brief Class for calculating hydraulic resistance of cylindrical bends with niche.
* @details Calculation based on diagrams (I.E. Idelchik, 1992):
* 6-7
* @image html 6-7.png
* This elemnt has a direction independent geometry, so Re computes as @f$ Re=|Re| @f$.
* @date Released 30.08.2022
* @author Ilya Konovalov
* @see CylindricalBend
*/
class CylindricalBendNiche :
	public CylindricalBend
{
public:
	/**
	* @brief Default constructor of cylindrical bend with niche element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	* @see CylindricalBend
	*/
	CylindricalBendNiche()
		: CylindricalBend()
	{
		// set default name of element
		name_ = "CylindricalBendNiche" + std::to_string(id_);
	};

	/**
	* @brief Recommended constructor of cylindrical bend with niche element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number. Negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of the bend element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Diameter of cross-section [m]
	*	- G[2]: Bending radius [m]
	*	- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
	calculates as 360 - G[3]
	*	- G[4]: Length of section before bend [m]; G[4] = 0 means, that
	bend located after collector, however G[4] > 0 means, that straight section L = G[4]
	located before bend
	* @see Service
	* @see CylindricalBend
	*/
	CylindricalBendNiche(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
		: CylindricalBend(name, Re, G)
	{
		// set name
		if (name != "")
		{
			// user defined name
			name_ = name;
		}
		else
		{
			// default name
			name_ = "CylindricalBendNiche" + std::to_string(id_);
		}

		if (autocalc)
		{
			calculateElement();
		}
	}

	/// @see IBaseHydraulicResistance::calculateElement()
	void calculateElement();

	/// @see IBaseHydraulicResistance::copy()
	virtual IBaseHydraulicResistance* copy() const;
};

