#include <libhydrocalc/cylindrical_confuser_curve.h>

using namespace hydrocalc;

hydrocalc::HydraulicResistance* hydrocalc::CylindricalConfuserCurve::copy() const
{
	return new CylindricalConfuserCurve(
		Re_,
		{
			rou_,
			D0_,
			L0_,
			L_,
			D1_,
			R0_
		},
		name_base_,
		vis_
	);
}

void hydrocalc::CylindricalConfuserCurve::evaluate()
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

void hydrocalc::CylindricalConfuserCurve::setGeometry(const std::vector<real>& G)
{
	CylindricalConfuserCurveDirect::setGeometry(G);

	diffuser_.setGeometry({ G.at(0), G.at(1), G.at(3), 0.0, G.at(4), G.at(5) });
}
