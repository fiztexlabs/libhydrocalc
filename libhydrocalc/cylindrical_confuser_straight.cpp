#include <libhydrocalc/cylindrical_confuser_straight.h>

using namespace hydrocalc;

HydraulicResistance* hydrocalc::CylindricalConfuserStraight::copy() const
{
	return new CylindricalConfuserStraight(
		Re_,
		{
			rou_,
			D0_,
			L0_,
			L_,
			D1_,
			alpha_
		},
		name_base_,
		vis_
	);
}

void hydrocalc::CylindricalConfuserStraight::evaluate()
{
	if (Re_ >= 0.0)
	{
		evaluateDirect();
	}
	else
	{
		diffuser_.evaluateDirect();

		lf_ = diffuser_.lf_;
		CSIlf_ = diffuser_.CSIlf_;
		CSIlr_ = diffuser_.CSIlr_;
		CSI_ = diffuser_.CSI_;
	}
}

void hydrocalc::CylindricalConfuserStraight::setGeometry(const std::vector<real>& G)
{
	CylindricalConfuserStraightDirect::setGeometry(G);

	diffuser_.setGeometry({ G.at(0), G.at(1), G.at(2), G.at(3), 0.0, G.at(4), G.at(4), G.at(5), 1.0 });
}
