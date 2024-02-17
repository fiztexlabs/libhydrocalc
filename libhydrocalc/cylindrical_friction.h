#pragma once
#include <libhydrocalc/friction.h>
#include <libhydrocalc/settings.h>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>

namespace hydrocalc
{
	/**
	* @brief Class for calculating hydraulic resistance of friction in
	* cylindrical elements.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 2-1
	* @image html 2-1.png
	* 2-3
	* @image html 2-3.png
	* 2-4
	* @image html 2-4.png
	* This elemnt has a direction independent
	* geometry, so Re computse as @f$ Re=|Re| @f$.
	* @author Ilya Konovalov
	* @date Released 01.08.2022
	*/
	class CylindricalFriction :
		public Friction
	{
	protected:
		/**
		* @brief Check cylindrical friction input values and raise exeptions or warnings
		* @details Error codes:
		*	- 1: Invalid size of vector of geometry characteristic
		*	- 2: One of element characteristics have an invalid value
		* @param G: Input vector of geometry characteristics
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @brief Evaluate relative friction loss coefficient (lf_) with respect to diagram 2-1
		void diagram21();

		/// @brief Evaluate relative friction loss coefficient (lf_) with respect to diagram 2-3
		void diagram23();

		/// @brief Evaluate relative friction loss coefficient (lf_) with respect to diagram 2-4
		void diagram24();

	public:
		/**
		* @brief Default constructor of cylindrical friction element.
		* @details Fields of element must be initialized by setters methods
		and after that function calculateElement() must be called.
		* @see Service
		*/
		CylindricalFriction() :
			Friction()
		{
			// set default name of element
			name_ = "CylindricalFriction " + std::to_string(id_);
		};

		/**
		* @brief Recommended constructor of cylindrical friction element.
		* @param name: String name of element
		* @param Re: Reynolds number, negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Diameter of cross-section [m]
		*	- G[2]: Length of element [m]
		*/
		CylindricalFriction(const real Re, const std::vector<real>& G, const std::string& name = "")
			: Friction(name, Re, G.at(1), G.at(0), M_PI * std::pow(0.5 * G.at(1), 2.0), G.at(2), Type::cylindrical)
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
				name_ = "CylindricalFriction " + std::to_string(id_);
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L_ = err;
			}

		};

		virtual ~CylindricalFriction() {};

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::getLength()
		virtual real getLength() override;

		/// @see HydraulicResistance::setLength()
		virtual void setLength(const real L) override;
	};
}