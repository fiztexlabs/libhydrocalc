#pragma once
#include <libhydrocalc/complex_resistance.h>
#include <libhydrocalc/cylindrical_friction.h>
#include <libhydrocalc/settings.h>
#include <string>
#include <math.h>
#include <cmath>
#include <libhydrocalc/exceptions.h>

namespace hydrocalc
{
	class CylindricalDiffuserStraight;

	/**
	* @brief Class for calculating hydraulic resistance of cylindrical confusers with
	* straight generatrix.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-23
	* 5-24
	* This elemnt has diagrams only for direct flow. For direction dependent flow
	* see hydrocalc::CylindricalConfuserStraight
	* @author Ilya Konovalov
	* @date Released 05.08.2022
	*/
	class CylindricalConfuserStraightDirect :
		public ComplexResistance
	{
	protected:
		/// @brief Friction part of hydraulic resistance of bend
		CylindricalFriction FrictionPart_;

		/// @brief Length of outlet section of confuser [m]
		real L0_ = 0.0;

		/// @brief Hydraulic diameter of inlet section of confuser [m]
		real D1_ = 0.0;

		/// @brief Cross-section area of inlet section of confuser [m2]
		real A1_ = 0.0;

		/// @brief Angle of confuser [deg]
		real alpha_ = 0.0;

		/**
		* @brief Check straight cylindrical confuser element input values and raise exeptions
		* or warnings.
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		* @param G: input vector of geometry characteristics, const std::vector<real>&
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-23
		void diagram523();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-24
		void diagram524();

		/// @see HydraulicResistance::evaluate()
		void evaluateDirect();

		friend CylindricalDiffuserStraight;

	public:
		/**
		* @brief Default constructor of straight cylindrical confuser element.
		*/
		CylindricalConfuserStraightDirect()
			: ComplexResistance()
		{
			type_ = "[CylindricalConfuserStraight]";

			internal_resistances_.push_back(&FrictionPart_);

			// set default name of element
			this->setName("CylindricalConfuserStraight " + std::to_string(id_));

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		}

		/**
		* @brief Recommended constructor of straight cylindrical confuser element.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Hydraulic diameter of confuser [m]
		*	- G[2]: Length of outlet section of confuser [m]
		*	- G[3]: Length of confuser [m]
		*	- G[4]: Diameter of inlet section of confuser [m]
		*	- G[5]: Angle of confuser [deg]
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		*/
		CylindricalConfuserStraightDirect(const real Re, const std::vector<real>& G, const std::string& name, const real vis)
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), G.at(3), vis, "[CylindricalConfuserStraight]")
		{
			internal_resistances_.push_back(&FrictionPart_);

			// set name
			if (name != "")
			{
				// user defined name
				this->setName(name);
			}
			else
			{
				// default name
				this->setName("CylindricalConfuserStraight " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L0_ = err;
				L_ = err;
				D1_ = err;
				alpha_ = err;
			}
			else
			{
				L0_ = G.at(2);
				D1_ = G.at(4);
				alpha_ = G.at(5);
			}

			// initialize friction element
			FrictionPart_ = CylindricalFriction(Re_, { rou_,D0_,L_ }, "friction");
			FrictionPart_.setExternalElementName(name_base_);

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;

			A1_ = M_PI * std::pow(0.5 * D1_, 2.0);

		}

		virtual ~CylindricalConfuserStraightDirect() {};

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @brief forbidden for this class
		void virtual evaluate() override;
	};
}

