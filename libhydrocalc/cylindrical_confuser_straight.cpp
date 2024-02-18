#include <libhydrocalc/cylindrical_confuser_straight.h>

using namespace hydrocalc;

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
