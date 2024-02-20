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
	class CylindricalConfuserCurve;

	/**
	* @brief Class for calculating hydraulic resistance of cylindrical diffusers with
	* curve generatrix.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-8
	* This elemnt has diagrams only for direct flow. For direction dependent flow
	* see hydrocalc::CylindricalConfuserCurve
	* @author Ilya Konovalov
	* @date Released 10.08.2022
	*/
	class CylindricalDiffuserCurveDirect :
		public ComplexResistance
	{
	protected:
		/// @brief Friction part of hydraulic resistance of bend
		CylindricalFriction FrictionPart_;

		/// @brief Length of outlet section of diffuser [m]
		real L1_ = 0.0;

		/// @brief Curve radius [m]
		real R0_ = 0.0;

		/// @brief Hydraulic diameter of outlet section of diffuser [m]
		real D1_ = 0.0;

		/// @brief Cross-section area of outlet section of diffuser [m2]
		real A1_ = 0.0;

		/**
		* @brief Check curve cylindrical diffuser element input values and raise exeptions
		* or warnings.
		* @param Re: input Reynolds number, const real
		* @param G: input vector of geometry characteristics, const std::vector<real>&
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @see HydraulicResistance::evaluate()
		void evaluateDirect();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-8
		void diagram58();

		friend CylindricalConfuserCurve;

	public:
		/**
		* @brief Default constructor of curve cylindrical diffuser element.
		*/
		CylindricalDiffuserCurveDirect()
			: ComplexResistance()
		{
			type_ = "[CylindricalDiffuserCurve]";

			internal_resistances_.push_back(&FrictionPart_);

			// set default name of element
			this->setName("CylindricalDiffuserCurve " + std::to_string(id_));

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		}

		/**
		* @brief Recommended constructor of curve cylindrical diffuser element.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Hydraulic diameter of diffuser [m]
		*	- G[2]: Length of diffuser [m]
		*	- G[3]: Length of outlet section of diffuser [m]
		*	- G[4]: Hydraulic diameter of outlet section of diffuser [m]
		*	- G[5]: Curve radius [m]
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		CylindricalDiffuserCurveDirect(const real Re, const std::vector<real>& G, const std::string& name, const real vis)
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), G.at(2), vis, "[CylindricalDiffuserCurve]")
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
				this->setName("CylindricalDiffuserCurve " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L_ = err;
				L1_ = err;
				D1_ = err;
				R0_ = err;
			}
			else
			{
				L1_ = G.at(3);
				D1_ = G.at(4);
				R0_ = G.at(5);
			}

			// initialize friction element
			FrictionPart_ = CylindricalFriction(Re_, { rou_,D0_,L_ }, "friction");
			FrictionPart_.setExternalElementName(name_base_);

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;

			A1_ = M_PI * std::pow(0.5 * D1_, 2.0);
		}

		virtual ~CylindricalDiffuserCurveDirect() {};

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @brief forbidden for this class
		virtual void evaluate() override;
	};
}

