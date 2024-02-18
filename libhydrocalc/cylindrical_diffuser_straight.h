#pragma once
#include <libhydrocalc/cylindrical_diffuser_straight_direct.h>
#include <libhydrocalc/cylindrical_confuser_straight_direct.h>

namespace hydrocalc
{
	/**
	* @brief Class for calculating hydraulic resistance of cylindrical diffusers with
	* straight generatrix.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-2
	* 5-7
	* 5-9
	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$,
	* element evaluated as confuser with corresponding geometry.
	* @see hydrocalc::CylindricalConfuserStraightDirect
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class CylindricalDiffuserStraight :
		public CylindricalDiffuserStraightDirect
	{
	private:
		/// @brief Confuser, for reverse flow calculations
		CylindricalConfuserStraightDirect confuser_;
	public:
		/**
		* @brief Default constructor of straight cylindrical diffuser element.
		*/
		CylindricalDiffuserStraight()
			: CylindricalDiffuserStraightDirect()
		{
			internal_resistances_.push_back(&confuser_);

			confuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

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
		*/
		CylindricalDiffuserStraight(const real Re, const std::vector<real>& G, const real I = 1.0, const std::string& name = "")
			: CylindricalDiffuserStraightDirect(Re, G, I, name), 
			confuser_(Re, {G.at(0), G.at(1), G.at(2), G.at(3), G.at(5), G.at(7)}, name_ + "{invert flow confuser}")
		{
			internal_resistances_.push_back(&confuser_);

			confuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		virtual ~CylindricalDiffuserStraight() {};

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;
	};

}