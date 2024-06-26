#include <libhydrocalc/cylindrical_friction.h>
#include <libmath/boolean.h>
#include <libhydrocalc/exceptions.h>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

void CylindricalFriction::evaluate()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);
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
		// direction independent
		real Re = std::abs(Re_);

		if (math::isEqual<real, real>(Re, static_cast<real>(0.0)))
		{
			CSI_ = CurrentSettings_.MAX_CSI;
			CSIlf_ = 0.0;
			CSIlr_ = CurrentSettings_.MAX_CSI;
			lf_ = 0.0;
		}
		else
		{
			if (rou_ == 0.0)
			{
				// diagram 2-1
				diagram21();
			}
			else
			{
				real Re2 = 2090.0 * std::pow((1.0 / relRou_), 0.0635);

				if (Re >= Re2)
				{
					// diagram 2-4
					diagram24();
				}
				else
				{
					// diagram 2-3
					diagram23();
				}
			}

			CSIlf_ = lf_ * (L_ / D0_);
			CSIlr_ = 0.0;
			CSI_ = CSIlf_ + CSIlr_;
		}
	}
}

HydraulicResistance* CylindricalFriction::copy() const
{
	return new CylindricalFriction(
		Re_,
		{
			rou_,
			D0_,
			L_
		},
		name_base_
	);
}

void hydrocalc::CylindricalFriction::diagram21()
{
	real Re = std::abs(Re_);

	diagram_ = "2-1";
	relRou_ = 0.0;

	// laminar
	if (Re <= 2000.0)
	{
		lf_ = 64.0 / Re;
	}
	// transient (approximation)
	if ((Re > 2000.0) && (Re < 4000.0))
	{
		lf_ = 7777777.77777767 * std::pow(Re, 2.0) - 364999.999999992 * Re + 6155.55555555541;
	}
	// turbulent
	if ((Re >= 4000.0) && (Re <= 100000.0))
	{
		lf_ = 0.3164 / std::pow(Re, 0.25);
	}
	// turbulent
	if (Re > 100000.0)
	{
		lf_ = std::pow((1.81 * std::log(Re) - 1.64), -2.0);
	}
}

void hydrocalc::CylindricalFriction::diagram23()
{
	real Re = std::abs(Re_);

	diagram_ = "2-3";
	real Re0 = 754.0 * std::exp(0.0065 / relRou_);
	real Re1 = 1160.0 * std::pow((1.0 / relRou_), 0.11);
	real Re2 = 2090.0 * std::pow((1.0 / relRou_), 0.0635);
	if ((Re > Re0) && (Re < Re1))
	{
		if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
		{
			if (relRou_ < 0.007)
			{
				relRou_ = procGeometryOutOfRange("rou/D0 (relative roughness)  < 0.007", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": rou/D0 (relative roughness) < 0.007"), 0.007);
			}
		}

		lf_ = 4.4 * std::pow(Re, -0.595) * std::exp(-0.00275 / relRou_);
	}
	if ((Re > Re1) && (Re < Re2))
	{
		real l1 = 0.0;
		real l2 = 0.0;
		if (relRou_ <= 0.007)
		{
			l1 = 0.032;
			l2 = 7.244 * std::pow(Re2, -0.643);
		}
		else
		{
			l1 = 0.0758 - (0.0109 / std::pow(relRou_, 0.286));
			l2 = 0.145 / std::pow(relRou_, -0.244);
		}

		lf_ = (l2 - l1) * std::exp(-std::pow(0.0017 * (Re2 - Re), 2.0)) + l1;
	}
}

void hydrocalc::CylindricalFriction::diagram24()
{
	real Re = std::abs(Re_);

	diagram_ = "2-4";
	real relRouLim = 15.0 / Re;
	if (rou_ < relRouLim * D0_)
	{
		if (Re <= 2000.0)
		{
			lf_ = 64.0 / Re;
		}
		// transient (approximation)
		if ((Re > 2000.0) && (Re < 4000.0))
		{
			lf_ = 7777777.77777767 * std::pow(Re, 2.0) - 364999.999999992 * Re + 6155.55555555541;
		}
		// turbulent
		if ((Re >= 4000.0) && (Re <= 100000.0))
		{
			lf_ = 0.3164 / std::pow(Re, 0.25);
		}
		// turbulent
		if (Re > 100000.0)
		{
			lf_ = std::pow((1.81 * std::log(Re) - 1.64), -2.0);
		}
	}
	else
	{
		if ((relRou_ >= 0.00008) && (relRou_ <= 0.0125))
		{
			lf_ = 0.11 * std::pow((relRou_ + (68 / Re)), 0.25);
		}
		else
		{
			lf_ = std::pow((2.0 * std::log((2.51 / (Re * std::sqrt(64.0 / Re))) + (relRou_ / 3.7))), -2.0);
		}
	}
}

real CylindricalFriction::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) < 0.0)
		{
			err += procInvalidValue("rou (roughness) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set rou (roughness) < 0.0"));
		}
		if (G.at(1) <= 0.0)
		{
			err += procInvalidValue("D0 (hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (hydraulic diameter) <= 0.0"));
		}
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("L (element length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L (element length) < 0.0"));
		}
	}

	return err;
}

void CylindricalFriction::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L_ = G.at(2);
	}
}

void CylindricalFriction::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L_,
		A_
	};
}