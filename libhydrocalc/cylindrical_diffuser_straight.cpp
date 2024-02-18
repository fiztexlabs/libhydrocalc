#include <libhydrocalc/cylindrical_diffuser_straight.h>

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
