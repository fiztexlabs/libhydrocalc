#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <libhydrocalc/cylindrical_friction.h>
#include <string>
#include <math.h>

namespace hydrocalc
{
	/**
	* @brief Class for calculating hydraulic resistance of cylindrical bends.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 6-1
	* @image html 6-1.png
	* 6-2
	* @image html 6-2.png
	* 6-7
	* @image html 6-7.png
	* 6-9
	* @image html 6-9.png
	* This elemnt has a direction independent geometry, so Re computes as @f$ Re=|Re| @f$.
	* @author Ilya Konovalov
	* @date Released 03.08.2022
	*/
	class CylindricalBend :
		public HydraulicResistanceBase
	{
	protected:
		/// @brief Friction part of hydraulic resistance of bend
		CylindricalFriction FrictionPart_;

		/// @brief Length of element [m]
		real L_ = 0.0;

		/// @brief Length of straight section before bend [m]
		real L0_ = 0.0;

		/// @brief Bending radius [m]
		real R0_ = 0.0;

		/// @brief Bending angle [deg]
		real delta_ = 0.0;

		/**
		* @brief Check input values and raise exeptions or warnings
		* @details Error codes:
		*	- 1: Invalid size of vector of geometry characteristic
		*	- 2: One of element characteristics have an invalid value
		* @param G: Input vector of geometry characteristics
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const;

	public:
		/**
		* @brief Default constructor of cylindrical bend element.
		*/
		CylindricalBend()
			: HydraulicResistanceBase()
		{};

		/**
		* @brief Recommended constructor of cylindrical bend element.
		* @details Automatically check inputs, initialize fields and calculate element
		* (if autocalc = 1).
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
		*/
		CylindricalBend(const real Re, const std::vector<real>& G, const std::string& name = "")
			: HydraulicResistanceBase(name, Re, G.at(1), G.at(1), M_PI* std::pow(0.5 * G.at(1), 2.0), 0.0, Type::cylindrical)
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
				name_ = "CylindricalBend " + std::to_string(id_);
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L0_ = err;
				R0_ = err;
			}
			else
			{
				L0_ = G.at(4);
				R0_ = G.at(2);
			}

			if (G.at(3) < 0)
			{
				delta_ = 360.0 - G.at(3);
			}
			else
			{
				delta_ = G.at(3);
			}

			L_ = (2.0 * M_PI * R0_ * delta_) / 360.0;

			FrictionPart_ = CylindricalFriction(Re_, { rou_,D0_,L_ }, name_ + "{friction}");

			// disable check parameters for internal part
			FrictionPart_.CurrentSettings_.checkInputs = 0;

		};

		virtual ~CylindricalBend() {};

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;
	};
}