#include <libhydrocalc/cylindrical_diffuser_straight.h>

using namespace hydrocalc;

HydraulicResistance* hydrocalc::CylindricalDiffuserStraight::copy() const
{
	return new CylindricalDiffuserStraight(
		Re_,
		{
			rou_,
			D0_,
			L0_,
			L_,
			L1_,
			Dout_,
			D1_,
			alpha_
		},
		name_base_,
		vis_,
		I_);
}

void hydrocalc::CylindricalDiffuserStraight::evaluate()
{
	if (Re_ >= 0.0)
	{
		evaluateDirect();
	}
	else
	{
		confuser_.evaluateDirect();

		lf_ = confuser_.lf_;
		CSIlf_ = confuser_.CSIlf_;
		CSIlr_ = confuser_.CSIlr_;
		CSI_ = confuser_.CSI_;
	}
}

void hydrocalc::CylindricalDiffuserStraight::setGeometry(const std::vector<real>& G)
{
	CylindricalDiffuserStraightDirect::setGeometry(G);

	confuser_.setGeometry({ G.at(0), G.at(1), G.at(2), G.at(3), G.at(5), G.at(7) });
}
