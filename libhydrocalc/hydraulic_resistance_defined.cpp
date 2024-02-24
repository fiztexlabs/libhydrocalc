#include <libhydrocalc/hydraulic_resistance_defined.h>
#include <libmath/boolean.h>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real hydrocalc::HydraulicResistanceDefined::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) <= 0.0)
		{
			err += procInvalidValue("D0 (hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (hydraulic diameter) <= 0.0"));
		}
		if (G.at(1) < 0.0)
		{
			err += procInvalidValue("CSI (defined direct local resistance coefficient) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set CSI (defined direct local resistance coefficient) < 0.0"));
		}
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("CSI (defined reverse local resistance coefficient) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set CSI (defined reverse local resistance coefficient) < 0.0"));
		}
	}

	return err;
}

HydraulicResistance* hydrocalc::HydraulicResistanceDefined::copy() const
{
	return new HydraulicResistanceDefined(
		Re_,
		{
			D0_,
			CSI_direct_,
			CSI_reverse_
		},
		name_base_,
		vis_
	);
}

void hydrocalc::HydraulicResistanceDefined::evaluate()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);

	real reversed = checkReversedFlow("Re < 0.0", ExceptionReversedFlow("reversed flow in the " + type_ + " element " + name_));

	if (std::isnan(reversed))
	{
		lf_ = reversed;
		CSI_ = reversed;
		CSIlr_ = reversed;
		CSIlf_ = reversed;
	}
	else
	{
		// direction dependent
		real Re = Re_;

		if (math::isEqual<real, real>(Re, static_cast<real>(0.0)))
		{
			CSI_ = CurrentSettings_.MAX_CSI;
			CSIlf_ = 0.0;
			CSIlr_ = CurrentSettings_.MAX_CSI;
			lf_ = 0.0;
		}
		else
		{
			if (Re < 0.0)
			{
				// reverse 
				CSI_ = CSI_reverse_;
			}
			else
			{
				CSI_ = CSI_direct_;
			}
		}
		CSIlr_ = CSI_;
		CSIlf_ = 0.0;
	}
}

void hydrocalc::HydraulicResistanceDefined::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		CSIlf_ = err;
		CSIlr_ = err;
		CSI_ = err;
	}
	else
	{
		D0_ = G.at(0);
		CSI_direct_ = G.at(1);
		CSI_reverse_ = G.at(2);
	}
}

void hydrocalc::HydraulicResistanceDefined::getGeometry(std::vector<real>& G)
{
	G =
	{
		D0_,
		CSI_direct_,
		CSI_reverse_,
		L_,
		A_
	};
}
