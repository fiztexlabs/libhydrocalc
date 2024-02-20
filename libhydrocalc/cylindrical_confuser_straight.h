#pragma once
#include <libhydrocalc/cylindrical_diffuser_straight_direct.h>
#include <libhydrocalc/cylindrical_confuser_straight_direct.h>

namespace hydrocalc
{
	/**
	* @brief Class for calculating hydraulic resistance of cylindrical confusers with
	* straight generatrix.
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 5-23
	* 5-24
	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$,
	* element evaluated as diffuser with corresponding geometry.
	* @see hydrocalc::CylindricalDiffuserStraightDirect
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class CylindricalConfuserStraight :
		public CylindricalConfuserStraightDirect
	{
	private:
		/// @brief Diffuser, for reverse flow calculations
		CylindricalDiffuserStraightDirect diffuser_;

	protected:
		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

	public:
		/**
		* @brief Default constructor of straight cylindrical confuser element.
		*/
		CylindricalConfuserStraight()
			: CylindricalConfuserStraightDirect()
		{
			internal_resistances_.push_back(&diffuser_);
			diffuser_.setExternalElementName(name_base_);

			diffuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

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
		CylindricalConfuserStraight(const real Re, const std::vector<real>& G, const std::string& name = "", const real vis = 1.0)
			: CylindricalConfuserStraightDirect(Re, G, name, vis),
			diffuser_(Re, { G.at(0), G.at(1), G.at(2), G.at(3), 0.0, G.at(4), G.at(4), G.at(5), 1.0 }, "invert flow diffuser", vis)
		{
			internal_resistances_.push_back(&diffuser_);
			diffuser_.setExternalElementName(name_base_);

			diffuser_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			diffuser_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		virtual ~CylindricalConfuserStraight() {};

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;
	};
}