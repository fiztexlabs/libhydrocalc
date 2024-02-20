#include <libhydrocalc/sharp_unexpected_size_change.h>
#include <libmath/boolean.h>
#include <cmath>
#include <algorithm>
#include <libhydrocalc/exceptions.h>

using namespace hydrocalc;

real SharpUnexpectedSizeChange::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) < 0.0)
		{
			err += procInvalidValue("rou (roughness) < 0.0", ExceptionInvalidValue(type_ + " " + type_ + " element " + name_ + ": try to set rou (roughness) < 0.0"));
		}
		if (G.at(1) <= 0.0)
		{
			err += procInvalidValue("D1 (first hydraulic diameter in the flow direction) <= 0.0", ExceptionInvalidValue(type_ + " " + type_ + " element " + name_ + ": try to set D1 (first hydraulic diameter in the flow direction) <= 0.0"));
		}
		if (G.at(2) <= 0.0)
		{
			err += procInvalidValue("D2 (second hydraulic diameter in the flow direction) <= 0.0", ExceptionInvalidValue(type_ + " " + type_ + " element " + name_ + ": try to set D2 (second hydraulic diameter in the flow direction) <= 0.0"));
		}
	}

	return err;
}

void SharpUnexpectedSizeChange::evaluate()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);
	A2_ = M_PI * std::pow(0.5 * std::max(D1_, D2_), 2.0);
	relRou_ = rou_ / D0_;
	
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
		if (math::isEqual(D1_, D2_))
		{
			lf_ = 0.0;
			CSI_ = 0.0;
			CSIlr_ = 0.0;
			CSIlf_ = 0.0;

			return void();
		}

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
			// inverse element for negative flow
			if (Re < 0.0)
			{
				// diagram 4-1
				if (D1_ > D2_)
				{
					diagram41();
				}
				// diagram 4-9
				else
				{
					diagram49();
				}
			}
			// for positive flow
			else
			{
				// diagram 4-1
				if (D1_ < D2_)
				{
					diagram41();
				}
				// diagram 4-9
				else
				{
					diagram49();
				}
			}
			CSI_ = CSIlr_ + CSIlf_;
		}
	}
}

HydraulicResistance* SharpUnexpectedSizeChange::copy() const
{
	return new SharpUnexpectedSizeChange(
		Re_,
		{
			rou_,
			D1_,
			D2_
		},
		name_base_
	);
}

void hydrocalc::SharpUnexpectedSizeChange::diagram41()
{
	diagram_ = "4-1";

	real Re = std::abs(Re_);

	if (Re >= 3.3e3)
	{
		CSIlr_ = std::pow(1.0 - (A2_ / A_), 2.0);
	}
	if ((Re < 3.3e3) && (Re >= 500.0))
	{
		CSIlr_ = -8.44556 - 26.163 * std::pow(1.0 - (A2_ / A_), 2.0) - 5.38086 * std::pow(1.0 - (A2_ / A_), 4.0)
			+ std::log(Re) * (6.007 + 18.5372 * std::pow(1.0 - (A2_ / A_), 2.0) + 3.9978 * std::pow(1.0 - (A2_ / A_), 4.0))
			+ std::pow(std::log(Re), 2.0) * (-1.02318 - 3.0916 * std::pow(1.0 - (A2_ / A_), 2.0) - 0.680943 * std::pow(1.0 - (A2_ / A_), 4.0));
	}
	if ((Re < 500.0) && (Re >= 10.0))
	{
		CSIlr_ = 3.62536 + 10.744 * std::pow(1.0 - (A2_ / A_), 2.0) - 4.41041 * std::pow(1.0 - (A2_ / A_), 4.0)
			+ (1.0 / std::log(Re)) * (-18.13 - 56.77855 * std::pow(1.0 - (A2_ / A_), 2.0) + 33.40344 * std::pow(1.0 - (A2_ / A_), 4.0))
			+ (1.0 / std::pow(std::log(Re), 2.0)) * (30.8558 + 99.9542 * std::pow(1.0 - (A2_ / A_), 2.0) - 62.78 * std::pow(1.0 - (A2_ / A_), 4.0))
			+ (1.0 / std::pow(std::log(Re), 3.0)) * (-13.217 - 53.9555 * std::pow(1.0 - (A2_ / A_), 2.0) - 33.8053 * std::pow(1.0 - (A2_ / A_), 4.0));
	}
	if (Re < 10.0)
	{
		CSIlr_ = 30.0 / Re;
	}
}

void hydrocalc::SharpUnexpectedSizeChange::diagram49()
{
	diagram_ = "4-9";

	real Re = std::abs(Re_);

	real err{ 0.0 };

	if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
	{
		// check Re for diagram 4-9
		if (Re < 1.e4)
		{
			err = procFlowOutOfRange("Re = " + std::to_string(Re) + " < 1.e4", ExceptionFlowOutOfRange(type_ + " " + type_ + " element " + name_ + ": Re < 1.e4"));
		}

		if (std::isnan(err))
		{
			CSIlf_ = err;
			CSIlr_ = err;
			CSI_ = err;

			return void();
		}
	}

	CSIlr_ = 0.5 * std::pow(1.0 - (A_ / A2_), 0.75);
}

void SharpUnexpectedSizeChange::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		D1_ = err;
		D2_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D1_ = G.at(1);
		D2_ = G.at(2);
		D0_ = std::min(D1_, D2_);
	}
}

void SharpUnexpectedSizeChange::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		D1_,
		D2_,
		A_,
		A2_
	};
}
