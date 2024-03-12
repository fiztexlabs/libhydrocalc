#include <libhydrocalc/cylindrical_confuser_straight_direct.h>
#include <libmath/boolean.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real CylindricalConfuserStraightDirect::checkGeometry(const std::vector<real>& G)
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
			err += procInvalidValue("D0 (confuser hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (confuser hydraulic diameter) < 0.0"));
		}
		if (G.at(5) > 180.0)
		{
			err += procGeometryOutOfRange("alpha (confuser angle) > 180.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set alpha (confuser angle) > 180.0"));
		}
		if (G.at(5) < 0.0)
		{
			err += procGeometryOutOfRange("alpha (confuser angle) < 0.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set alpha (confuser angle) < 0.0"));
		}
		if (G.at(3) < 0.0)
		{
			err += procInvalidValue("L (confuser length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L (confuser length) < 0.0"));
		}
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("L0 (confuser outlet section length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L0 (confuser outlet section length) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("Din (confuser inlet diameter) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set Din (confuser inlet diameter) < 0.0"));
		}
		if (G.at(4) < G.at(1))
		{
			err += procGeometryOutOfRange("Din (confuser inlet diameter) < D0 (confuser hydraulic diamater)", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set Din (confuser inlet diameter) < D0 (confuser hydraulic diamater)"));
		}

		// check confuser diameters and length consistency
		real d_out = G.at(1) + 2.0 * G.at(3) * std::tan(0.5 * G.at(5) / (180.0 / M_PI));
		if (!math::isEqual(G.at(4), d_out))
		{
			err += procInvalidValue("Inconsistent geometry. Din (confuser inlet diameter) != D0 + 2*L*tan(0.5*alpha)", ExceptionInvalidValue(type_ + " element " + name_ + ": Inconsistent geometry. Din (confuser inlet diameter) != D0 + 2*L*atan(0.5*alpha)"));
		}
	}

	return err;
}

void CylindricalConfuserStraightDirect::evaluateDirect()
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
			real n0d = A_ / A1_;

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

			if (Re > 50.0)
			{
				// diagram 5-23 (turbulent)
				diagram523();
			}
			else
			{
				// diagram 5-24 (laminar)
				diagram524();
			}
		}
	}
}

HydraulicResistance* CylindricalConfuserStraightDirect::copy() const
{
	real err = procNonExixtantFunc("evaluate", ExceptionNonExistentFunction("Try to call function ""copy"", forbidden for direct " + type_ + " element: " + name_));

	return nullptr;
}

void hydrocalc::CylindricalConfuserStraightDirect::diagram523()
{
	diagram_ = "5-23";

	real n0d = A_ / A1_;

	real Re = std::abs(Re_);

	real err{ 0.0 };

	if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
	{
		// check Re for diagram 5-23
		if (Re < 1.e5)
		{
			err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 1.e5", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 1.e5"));
		}

		if (std::isnan(err))
		{
			CSIlf_ = err;
			CSIlr_ = err;
			CSI_ = err;

			return void();
		}
	}

	real csi_lf1 = (lf_ / (8.0 * std::sin((0.5 * alpha_) / (180.0 / M_PI)))) * (1.0 - std::pow(n0d, 2.0));

	real xd = L0_ / D0_;

	real avgXd = std::log(1.0 + 2.0 * xd * std::tan((0.5 * alpha_) / (180.0 / M_PI)))
		/ (2.0 * std::tan((0.5 * alpha_) / (180.0 / M_PI)));

	CSIlf_ = csi_lf1 * (1.0 + (0.5 / std::pow(1.5, avgXd)));

	real ap = 0.01745 * alpha_;
	CSIlr_ = (-0.0125 * std::pow(n0d, 4.0) + 0.0224 * std::pow(n0d, 3.0) - 0.00723 * std::pow(n0d, 3.0) + 0.00444 * n0d - 0.00745)
		* (std::pow(ap, 3.0) - 2.0 * M_PI * std::pow(ap, 2.0) - 10.0 * ap);

	CSI_ = CSIlf_ + CSIlr_;
}

void hydrocalc::CylindricalConfuserStraightDirect::diagram524()
{
	diagram_ = "5-24";

	real n0d = A_ / A1_;

	real Re = std::abs(Re_);

	CSIlr_ = 0.0;

	real A = 20.5 / (std::pow(std::tan((alpha_) / (180.0 / M_PI)), 0.75) * std::pow(n0d, 0.5));
	CSIlf_ = A / Re;

	CSI_ = CSIlf_ + CSIlr_;

}

void CylindricalConfuserStraightDirect::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L0_ = err;
		L_ = err;
		D1_ = err;
		alpha_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L0_ = G.at(2);
		L_ = G.at(3);
		D1_ = G.at(4);
		alpha_ = G.at(5);
	}

	FrictionPart_.setGeometry({ rou_, D0_, L_ });
}

void hydrocalc::CylindricalConfuserStraightDirect::evaluate()
{
	real err = procNonExixtantFunc("evaluate", ExceptionNonExistentFunction("Try to call function ""evaluate"", forbidden for direct " + type_ + " element: " + name_));

	return void();
}

void CylindricalConfuserStraightDirect::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		L_,
		D1_,
		alpha_,
		A_,
		A1_
	};
}
