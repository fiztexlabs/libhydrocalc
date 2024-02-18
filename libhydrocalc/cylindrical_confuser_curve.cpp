#include "cylindrical_confuser_curve.h"

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
