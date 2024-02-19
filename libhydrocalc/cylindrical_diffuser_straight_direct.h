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
	class CylindricalConfuserStraight;

	/**
	* @brief Class for calculating hydraulic resistance of cylindrical diffusers with
	* straight generatrix.
	* @todo Add approximation of @f$ k_d @f$ with diagram 5-2 for
	* cases with I > 1
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-2
	* 5-7
	* 5-9
	* This elemnt has diagrams only for direct flow. For direction dependent flow
	* see hydrocalc::CylindricalDiffuserStraight
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class CylindricalDiffuserStraightDirect :
		public ComplexResistance
	{
	private:
		/// @brief Friction part of hydraulic resistance of bend
		CylindricalFriction FrictionPart_;

		/// @brief Length of inlet section of diffuser [m]
		real L0_ = 0.0;

		/// @brief Length of outlet section of diffuser [m]
		real L1_ = 0.0;

		/// @brief Hydraulic diameter of outlet section of diffuser [m]
		real D1_ = 0.0;

		/// @brief Diameter of outlet of diffuser [m]
		real Dout_ = 0.0;

		/// @brief Cross-section area of outlet section of diffuser [m2]
		real A1_ = 0.0;

		/// @brief Angle of diffuser [deg]
		real alpha_ = 0.0;

		/// @brief Turbulence intensity, @f$ I=\frac{w_0}{w_max} @f$
		real I_ = 0.0;

	protected:
		/**
		* @brief Check straight cylindrical diffuser element input values and raise exeptions
		* or warnings.
		* @param Re: input Reynolds number, const real
		* @param G: input vector of geometry characteristics, const std::vector<real>&
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-2
		void diagram52();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-7
		void diagram57();

		/// @brief Evaluate rhydraulic resistance with respect to diagram 5-9
		void diagram59();

		/// @see HydraulicResistance::evaluate()
		void evaluateDirect();

		friend CylindricalConfuserStraight;

	public:
		/**
		* @brief Default constructor of straight cylindrical diffuser element.
		*/
		CylindricalDiffuserStraightDirect()
			: ComplexResistance()
		{
			internal_resistances_.push_back(&FrictionPart_);

			// set default name of element
			this->setName("CylindricalDiffuserStraightDirect " + std::to_string(id_));

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		}

		/**
		* @brief Recommended constructor of straight cylindrical diffuser element.
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param I: Turbulence intensity, @f$ I=\frac{w_0}{w_max} @f$. If @f$ I=1 @f$
		* velocity profile before diffuser is straight and influece of hit coefficient @f$ k_d @f$
		* doesn't matter. Otherwise @f$ k_d @f$ should be taken into account with diagram 5-2
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Hydraulic diameter of diffuser [m]
		*	- G[2]: Length of inlet section of diffuser [m]
		*	- G[3]: Length of diffuser [m]
		*	- G[4]: Length of outlet section of diffuser [m]
		*	- G[5]: Diameter of the outlet of diffuser[m]
		*	- G[6]: Hydraulic diameter of outlet section of diffuser [m]
		*	- G[7]: Angle of diffuser [deg]
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		CylindricalDiffuserStraightDirect(const real Re, const std::vector<real>& G, const real I = 1.0, const std::string& name = "")
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), G.at(3), "straight cylindrical diffuser"), I_(I)
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
				this->setName("CylindricalDiffuserStraightDirect " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				L0_ = err;
				L_ = err;
				L1_ = err;
				Dout_ = err;
				D1_ = err;
				alpha_ = err;
			}
			else
			{
				L0_ = G.at(2);
				L1_ = G.at(4);
				Dout_ = G.at(5);
				D1_ = G.at(6);
				alpha_ = G.at(7);
			}

			if (I < 1.0)
			{
				err = procInvalidValue("I (turbulence intensity) < 1.0", ExceptionInvalidValue("Straiht cylindrical diffuser element " + name_ + ": try to set I (turbulence intensity) < 1.0"));
				if (std::isnan(err))
				{
					Re_ = err;
				}
			}

			// initialize friction element
			FrictionPart_ = CylindricalFriction(Re_, { rou_,D0_,L_ }, "friction");
			FrictionPart_.setExternalElementName(name_base_);

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;

			A1_ = M_PI * std::pow(0.5 * D1_, 2.0);

		}

		virtual ~CylindricalDiffuserStraightDirect() {};

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @brief forbidden for this class
		virtual void evaluate() override;
	};
}
