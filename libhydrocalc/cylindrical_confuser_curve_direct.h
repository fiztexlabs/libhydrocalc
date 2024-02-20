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
	class CylindricalDiffuserCurve;

	/**
	* @brief Class for calculating hydraulic resistance of cylindrical confusers with
	* curve generatrix.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-23
	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
	* element create CurveCylindricalDiffuser in function createDiffuser and calculate it.
	* @author Ilya Konovalov
	* @date Released 11.08.2022
	*/
	class CylindricalConfuserCurveDirect :
		public ComplexResistance
	{
	private:
		/// @brief Friction part of hydraulic resistance of bend
		CylindricalFriction FrictionPart_;

		/// @brief Length of outlet section of confuser [m]
		real L0_ = 0.0;

		/// @brief Curve radius [m]
		real R0_ = 0.0;

		/// @brief Hydraulic diameter of inlet section of confuser [m]
		real D1_ = 0.0;

		/// @brief Cross-section area of inlet section of confuser [m2]
		real A1_ = 0.0;

	protected:
		/**
		* @brief Check curve cylindrical confuser element input values and raise exeptions
		* or warnings.
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		* @param Re: input Reynolds number, const real
		* @param G: input vector of geometry characteristics, const std::vector<real>&
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @see HydraulicResistance::evaluate()
		void evaluateDirect();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-23
		void diagram523();

		friend CylindricalDiffuserCurve;

	public:
		/**
		* @brief Default constructor of curve cylindrical confuser element.
		*/
		CylindricalConfuserCurveDirect()
			: ComplexResistance()
		{
			type_ = "[CylindricalConfuserCurve]";

			internal_resistances_.push_back(&FrictionPart_);

			// set default name of element
			this->setName("CylindricalConfuserCurve " + std::to_string(id_));

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		}

		/**
		* @brief Recommended constructor of curve cylindrical confuser element.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Hydraulic diameter of confuser [m]
		*	- G[2]: Length of outlet section of confuser [m]
		*	- G[3]: Length of confuser [m]
		*	- G[4]: Hydraulic diameter of inlet section of confuser [m]
		*	- G[5]: Curve radius [m]
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		CylindricalConfuserCurveDirect(const real Re, const std::vector<real>& G, const std::string& name, const real vis)
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), G.at(3), vis, "[CylindricalConfuserCurve]")
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
				this->setName("CylindricalConfuserCurve " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L_ = err;
				L0_ = err;
				D1_ = err;
				R0_ = err;
			}
			else
			{
				L0_ = G.at(2);
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

		virtual ~CylindricalConfuserCurveDirect() {};

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @brief forbidden for this class
		virtual void evaluate() override;
	};
}