#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

namespace hydrocalc
{
	/**
	* @brief Defined hydraulic resistance coefficient with direction dependent CSI
	* @author Ilya Konovalov
	* @date Released 24.02.2024
	*/
	class HydraulicResistanceDefined :
		public HydraulicResistanceBase
	{
	protected:
		/// @brief Hydraulic resistance for direct flow
		real CSI_direct_ = 0.0;

		/// @brief Hydraulic resistance for reverse flow
		real CSI_reverse_ = 0.0;

		/**
		* @brief Check input values and raise exeptions or warnings
		* @param G: Input vector of geometry characteristics
		* @throw ExceptionInvalidValue
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

	public:
		/**
		* @brief Default constructor of defined hydraulic resistance element.
		*/
		HydraulicResistanceDefined()
			: HydraulicResistanceBase()
		{
			type_ = "[HydraulicResistanceDefined]";

			this->setName("HydraulicResistanceDefined " + std::to_string(id_));
		};


		/**
		* @brief Recommended constructor of defined hydraulic resistance element.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the defined hydraulic resistance element:
		*	- G[0]: Diameter of cross-section [m]
		*	- G[1]: Defined local resistance coefficient for direct flow
		*	- G[2]: Defined local resistance coefficient for reverse flow
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		* @throw ExceptionInvalidValue
		*/
		HydraulicResistanceDefined(const real Re, const std::vector<real>& G, const std::string& name = "", const real vis = 1.0)
			: HydraulicResistanceBase(name, Re, G.at(0), 0.0, M_PI* std::pow(0.5 * G.at(0), 2.0), 0.0, vis, "[HydraulicResistanceDefined]")
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
				this->setName("HydraulicResistanceDefined " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				CSIlf_ = err;
				CSIlr_ = err;
				CSI_ = err;
			}
			else
			{
				CSI_direct_ = G.at(1);
				CSI_reverse_ = G.at(2);
				if (Re_ >= 0.0)
				{
					// set direct defined hydraulic resistance coefficient
					CSI_ = CSI_direct_;
				}
				else
				{
					// set reversed defined hydraulic resistance coefficient
					CSI_ = CSI_reverse_;
				}
				CSIlr_ = CSI_;
			}

		};

		virtual ~HydraulicResistanceDefined() {};

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;
	};
}