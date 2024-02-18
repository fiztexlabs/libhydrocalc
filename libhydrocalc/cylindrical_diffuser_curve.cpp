#include <libhydrocalc/cylindrical_diffuser_curve.h>

void hydrocalc::CylindricalDiffuserCurve::evaluate()
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

void hydrocalc::CylindricalDiffuserCurve::setGeometry(const std::vector<real>& G)
{
	CylindricalDiffuserCurveDirect::setGeometry(G);

	confuser_.setGeometry({ G.at(0), G.at(1), 0.0, G.at(2), G.at(4), G.at(5) });
}
