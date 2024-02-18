#pragma once
#include <libhydrocalc/cylindrical_diffuser_curve_direct.h>
#include <libhydrocalc/cylindrical_confuser_curve_direct.h>

namespace hydrocalc
{
	/**
	* @brief Class for evaluating hydraulic resistance of cylindrical confuser
	* with curve generatrix.
	* @details Element hydraulic resistance depends on flow direction:
	* for negative flow (Re<0) hydraulic resistance calculated as for 
	* diffuser (hydrocalc::CylindricalDiffuserCurveDirect)
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class CylindricalConfuserCurve :
		public CylindricalConfuserCurveDirect
	{
	private:
		/// @brief Diffuser, for reverse flow calculations
		CylindricalDiffuserCurveDirect diffuser_;
	public:
		/**
		* @brief Default constructor of straight cylindrical confuser element.
		*/
		CylindricalConfuserCurve()
			: CylindricalConfuserCurveDirect()
		{
			internal_resistances_.push_back(&diffuser_);

			diffuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

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
		*/
		CylindricalConfuserCurve(const real Re, const std::vector<real>& G, const std::string& name = "")
			: CylindricalConfuserCurveDirect(Re, G, name),
			diffuser_(Re, { G.at(0), G.at(1), G.at(3), 0.0, G.at(4), G.at(5) }, name_ + "{invert flow diffuser}")
		{
			internal_resistances_.push_back(&diffuser_);

			diffuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		virtual ~CylindricalConfuserCurve() {};

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;
	};
}