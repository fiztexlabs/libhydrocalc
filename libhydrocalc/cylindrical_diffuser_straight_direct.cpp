#include <libhydrocalc/cylindrical_diffuser_straight_direct.h>
#include <libhydrocalc/approximations/f52.h>
#include <libhydrocalc/approximations/e59.h>
#include <libmath/boolean.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real CylindricalDiffuserStraightDirect::checkGeometry(const std::vector<real>& G)
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
			err += procInvalidValue("D0 (diffuser hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (diffuser hydraulic diameter) < 0.0"));
		}
		if (G.at(7) < 3.0)
		{
			err += procGeometryOutOfRange("alpha (diffuser angle) < 3.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set alpha (diffuser angle) < 3.0"));
		}
		if (G.at(7) > 180.0)
		{
			err += procGeometryOutOfRange("alpha (diffuser angle) > 180.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set alpha (diffuser angle) > 180.0"));
		}
		if (G.at(3) < 0.0)
		{
			err += procInvalidValue("L (diffuser length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L (diffuser length) < 0.0"));
		}
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("L0 (diffuser inlet section length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L0 (diffuser inlet section length) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("L1 (diffuser outlet section length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L1 (diffuser outlet section length) < 0.0"));
		}
		if (G.at(5) < 0.0)
		{
			err += procInvalidValue("Dout (diffuser outlet diameter) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set Dout (diffuser outlet diameter) < 0.0"));
		}
		if (G.at(5) < G.at(1))
		{
			err += procGeometryOutOfRange("Dout (diffuser outlet diameter) < D0 (diffuser hydraulic diamater)", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set Dout (diffuser outlet diameter) < D0 (diffuser hydraulic diamater)"));
		}
		if (G.at(6) < 0.0)
		{
			err += procInvalidValue("D1 (diffuser outlet section hydraulic diameter) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D1 (diffuser outlet section hydraulic diameter) < 0.0"));
		}

		// check diffuser diameters and length consistency
		real d_out = G.at(1) + 2.0 * G.at(3) * std::atan(0.5 * G.at(7) / (180.0 / M_PI));
		if (!math::isEqual(G.at(5), d_out))
		{
			err += procInvalidValue("Inconsistent geometry. Dout (diffuser outlet diameter) != D0 + 2*L*atan(0.5*alpha)", ExceptionInvalidValue(type_ + " element " + name_ + ": Inconsistent geometry. Dout (diffuser outlet diameter) != D0 + 2*L*atan(0.5*alpha)"));
		}
	}

	return err;
}

void CylindricalDiffuserStraightDirect::evaluateDirect()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);
	A1_ = M_PI * std::pow(0.5 * D1_, 2.0);
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
		// direct
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
			real n1d = A1_ / A_;

			FrictionPart_.evaluate();
			lf_ = FrictionPart_.getRelFrictionCoeff();

			// if angle = 0, diffuser reduced to friction
			if (alpha_ == 0.0)
			{
				CSIlf_ = FrictionPart_.getFrictionPartCoeff();
				CSIlr_ = FrictionPart_.getGeometryPartCoeff();
				CSI_ = FrictionPart_.getLocalResistanceCoeff();
				return void();
			}

			if (D1_ == Dout_)
			{
				if (Re > 50.0)
				{
					// diagram 5-2 (turbulent)
					diagram52();
				}
				else
				{
					// diagram 5-7 (laminar)
					diagram57();
				}
			}
			else
			{
				// diagram 5-9
				diagram59();
			}
		}
	}
}

HydraulicResistance* CylindricalDiffuserStraightDirect::copy() const
{
	return new CylindricalDiffuserStraightDirect(
		Re_,
		{
			rou_,
			D0_,
			L0_,
			L_,
			L1_,
			Dout_,
			D1_,
			alpha_
		},
		I_,
		name_);
}

void hydrocalc::CylindricalDiffuserStraightDirect::diagram52()
{
	diagram_ = "5-2";

	real Re = std::abs(Re_);

	real err{ 0.0 };

	if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
	{
		// check Re for diagram 5-2
		if (Re < 0.5e5)
		{
			err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 0.5e5", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 0.5e5"));
		}
		if (Re > 6.e5)
		{
			err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 6.e5", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 6.e5"));
		}

		if (std::isnan(err))
		{
			CSIlf_ = err;
			CSIlr_ = err;
			CSI_ = err;

			return void();
		}
	}

	real n1d = A1_ / A_;

	real csi_lf1 = (lf_ / (8.0 * std::sin((0.5 * alpha_) / (180.0 / M_PI)))) * (1.0 - (1.0 / n1d));

	real xd = L1_ / D0_;

	real avgXd = std::log(1.0 + 2.0 * xd * std::tan((0.5 * alpha_) / (180.0 / M_PI)))
		/ (2.0 * std::tan((0.5 * alpha_) / (180.0 / M_PI)));

	CSIlf_ = csi_lf1 * (1.0 + (0.5 / std::pow(1.5, avgXd)));

	// constraint for Re in calculations of hit coefficient F
	real Re1 = std::max(0.5e5, std::min(Re, 6.e5));
	// calculate F with approximation
	real F = 0.0;
	real inputF[2] = { alpha_, Re1 };
	F52Calc(inputF, 1, &F, 1, NULL, 0, 0);

	real csi_exp = F * std::pow((1.0 - (1.0 / n1d)), 1.92);

	real ad = 0.924 / (1.0 + 1.3e-5 * std::pow(alpha_, 3.14));
	real bd = (0.3 + 1.55 * std::pow(1.1, -alpha_)) / (1.0 + 1.03e-8 * std::pow(L0_ / D0_, 7.5));
	long double cd = 1.05 / (1.0 + 2.3e-62 * std::pow(Re, 11));

	real csi_turb = 0.044 * std::pow(0.345 * alpha_, ad) * (1.0 - std::pow(0.2 * n1d + 0.8, -3.82)) * std::pow(0.154 * (L0_ / D0_), bd)
		* std::pow(2.31e-6 * Re + 0.2 + 2.54 * std::pow((1.0 + 0.081 * alpha_), -1.51), static_cast<real>(cd));

	CSIlr_ = csi_exp + csi_turb;

	CSI_ = CSIlf_ + CSIlr_;
}

void hydrocalc::CylindricalDiffuserStraightDirect::diagram57()
{
	diagram_ = "5-7";

	real Re = std::abs(Re_);

	real n1d = A1_ / A_;

	CSIlr_ = 0.0;

	real A = (20.0 * std::pow(n1d, 0.33)) / std::pow(std::tan((alpha_) / (180.0 / M_PI)), 0.75);
	CSIlf_ = A / Re;

	CSI_ = CSIlf_ + CSIlr_;
}

void hydrocalc::CylindricalDiffuserStraightDirect::diagram59()
{
	diagram_ = "5-9";

	// calculate CSI with approximation
	real np = (M_PI * std::pow(0.5 * Dout_, 2.0)) / A_;
	real inputE[2] = { std::max(1.5, std::min(20.0, np)), std::max(0.5, std::min(14.0, L_ / D0_)) };
	E59Calc(inputE, 1, &CSIlr_, 1, NULL, 0, 0);

	CSIlf_ = 0.;
	CSI_ = CSIlr_ + CSIlf_;
}

void CylindricalDiffuserStraightDirect::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L0_ = err;
		L_ = err;
		L1_ = err;
		Dout_ = err;
		D1_ = err;
		alpha_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L0_ = G.at(2);
		L_ = G.at(3);
		L1_ = G.at(4);
		Dout_ = G.at(5);
		D1_ = G.at(6);
		alpha_ = G.at(7);
	}

	FrictionPart_.setGeometry({ rou_, D0_, L_ });
}

void CylindricalDiffuserStraightDirect::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		L_,
		L1_,
		Dout_,
		D1_,
		alpha_,
		A_,
		A1_
	};
}

void hydrocalc::CylindricalDiffuserStraightDirect::evaluate()
{
	real err = procNonExixtantFunc("evaluate", ExceptionNonExistentFunction("Try to call function ""evaluate"", forbidden for direct " + type_ + " element: " + name_));

	return void();
}