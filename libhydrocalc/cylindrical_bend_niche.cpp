#include <libhydrocalc/cylindrical_bend_niche.h>

using namespace hydrocalc;

HydraulicResistance* hydrocalc::CylindricalBendNiche::copy() const
{
	return new CylindricalBendNiche(
		Re_,
		{
			rou_,
			D0_,
			R0_,
			delta_,
			L0_
		},
		name_,
		vis_
	);
}

void hydrocalc::CylindricalBendNiche::evaluate()
{
	CylindricalBend::evaluate();

	diagram_ = "6-7";

	CSIlf_ = 1.2 * CSIlf_;
	CSIlr_ = 1.2 * CSIlr_;
	CSI_ = 1.2 * CSI_;
}
