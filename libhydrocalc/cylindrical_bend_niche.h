#pragma once
#include <libhydrocalc/cylindrical_bend.h>

namespace hydrocalc
{
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
	protected:
		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;
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
			type_ = "[CylindricalBendNiche]";

			// set default name of element
			this->setName("CylindricalBendNiche " + std::to_string(id_));
		};

		/**
		* @brief Recommended constructor of cylindrical bend element with niche.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Diameter of cross-section [m]
		*	- G[2]: Bending radius [m]
		*	- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
		* calculates as 360 - G[3]
		*	- G[4]: Length of section before bend [m]; G[4] = 0 means, that
		* bend located after collector, however G[4] > 0 means, that straight section L = G[4]
		* located before bend
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		* @throw ExceptionInvalidValue
		*/
		CylindricalBendNiche(const real Re, const std::vector<real>& G, const std::string& name = "", const real vis = 1.0)
			: CylindricalBend(Re, G, name, vis)
		{
			type_ = "[CylindricalBendNiche]";

			// set name
			if (name != "")
			{
				// user defined name
				this->setName(name);
			}
			else
			{
				// default name
				this->setName("CylindricalBendNiche " + std::to_string(id_));
			}
		}

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;
	};
}
