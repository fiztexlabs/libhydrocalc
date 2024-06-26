#pragma once
#include <libhydrocalc/cylindrical_diffuser_curve_direct.h>
#include <libhydrocalc/cylindrical_confuser_curve_direct.h>

namespace hydrocalc
{
	/**
	* @brief Class for evaluating hydraulic resistance of cylindrical diffuser
	* with curve generatrix.
	* @details Element hydraulic resistance depends on flow direction:
	* for negative flow (Re<0) hydraulic resistance calculated as for
	* confuser (hydrocalc::CylindricalConfuserCurveDirect)
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class CylindricalDiffuserCurve :
		public CylindricalDiffuserCurveDirect
	{
	private:
		/// @brief Confuser, for reverse flow calculations
		CylindricalConfuserCurveDirect confuser_;

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;
	public:
		/**
		* @brief Default constructor of curve cylindrical diffuser element.
		*/
		CylindricalDiffuserCurve()
			: CylindricalDiffuserCurveDirect()
		{
			internal_resistances_.push_back(&confuser_);
			confuser_.setExternalElementName(name_base_);

			confuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

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
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		CylindricalDiffuserCurve(const real Re, const std::vector<real>& G, const std::string& name = "", const real vis = 1.0)
			: CylindricalDiffuserCurveDirect(Re, G, name, vis),
			confuser_(Re, { G.at(0), G.at(1), 0.0, G.at(2), G.at(4), G.at(5) }, "invert flow confuser", vis)
		{
			internal_resistances_.push_back(&confuser_);
			confuser_.setExternalElementName(name_base_);

			confuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			confuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		virtual ~CylindricalDiffuserCurve() {};

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;
	};
}