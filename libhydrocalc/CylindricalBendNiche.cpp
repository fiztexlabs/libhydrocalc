#include <pch.h>
#include <HydraulicResistances/CylindricalBendNiche.h>

void CylindricalBendNiche::calculateElement()
{
	diagram_ = "6-7";
	CSIlf_ = 1.2 * CSIlf_;
	CSIlr_ = 1.2 * CSIlr_;
	CSI_ = 1.2 * CSI_;
}

IBaseHydraulicResistance* CylindricalBendNiche::copy() const
{
	return new CylindricalBendNiche(name_, Re_,
		{
			rou_,
			D0_,
			R0_,
			delta_,
			L0_
		}
	);
}
