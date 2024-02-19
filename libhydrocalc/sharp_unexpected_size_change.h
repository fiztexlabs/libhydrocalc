#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <string>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <vector>

namespace hydrocalc
{
	/**
	* @brief Class for calculating unexpected size changes with sharp edges.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 4-1
	* 4-9
	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
	* if element is expansion, than it turns to constriction and vice versa. Also if @f$ D_0 < D_1 @f$
	* element is expansion, othervise - constriction.
	* @author Ilya Konovalov
	* @date Released 12.08.2022
	*/
	class SharpUnexpectedSizeChange :
		public HydraulicResistanceBase
	{
	private:
		/// @brief Cross-section area of additional section (inlet if constriction or outlet if expansion) [m2]
		real A2_ = 0.0;

		/// @brief Diameter 1 [m]
		real D1_ = 0.0;

		/// @brief Diameter 2 [m]
		real D2_ = 0.0;

	protected:
		/**
		* @brief Check element input values and raise exeptions or warnings
		* @param Re: Input Reynolds number
		* @param G: Input vector of geometry characteristics
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @brief Evaluate rhydraulic resistance with respect to diagram 4-1
		void diagram41();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 4-9
		void diagram49();

	public:
		/**
		* @brief Default constructor of unexpected size changes with sharp edges.
		* @details Fields of element must be initialized by setters methods
		and after that function calculateElement() must be called.
		* @see Service
		*/
		SharpUnexpectedSizeChange()
			: HydraulicResistanceBase()
		{
			// set default name of element
			this->setName("UnexpectedSizeChange(constriction) " + std::to_string(id_));
		};

		/**
		* @brief Recommended constructor of unexpected size changes with sharp edges.
		* @param name: String name of element
		* @param Re: Reynolds number, negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Diameter 1 (in the flow direction) [m] 
		*	- G[2]: Diameter 2 (in the flow direction) [m]
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		SharpUnexpectedSizeChange(const real Re, const std::vector<real>& G, const std::string& name = "")
			: HydraulicResistanceBase(name, Re, std::min(G.at(1), G.at(2)), G.at(0), M_PI* std::pow(0.5 * std::min(G.at(1), G.at(2)), 2.0), 0.0, "sharp unexpected size change")
		{
			// set name
			if (name != "")
			{
				// user defined name
				this->setName(name);
			}
			else
			{
				// default name
				if (G.at(1) > G.at(2))
				{
					this->setName("UnexpectedSizeChange(constriction) " + std::to_string(id_));
				}
				else
				{
					this->setName("UnexpectedSizeChange(expansion) " + std::to_string(id_));
				}
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				D1_ = err;
				D2_ = err;
			}
			else
			{
				D1_ = G.at(1);
				D2_ = G.at(2);
			}

			A2_ = M_PI * pow(0.5 * std::max(D1_, D2_), 2.0);

		};

		virtual ~SharpUnexpectedSizeChange() {};

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;
	};
}

