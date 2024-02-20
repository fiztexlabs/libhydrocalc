#include <libhydrocalc/cylindrical_confuser_curve_direct.h>
#include <libhydrocalc/approximations/e523.h>
#include <libmath/boolean.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real CylindricalConfuserCurveDirect::checkGeometry(const std::vector<real>& G)
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
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("L0 (confuser outlet section length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L0 (confuser outlet section length) < 0.0"));
		}
		if (G.at(3) < 0.0)
		{
			err += procInvalidValue("L (confuser length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L (confuser length) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("Din (confuser inlet diameter) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set Din (confuser inlet diameter) < 0.0"));
		}
		if (G.at(4) < G.at(1))
		{
			err += procGeometryOutOfRange("Din (confuser inlet diameter) < D0 (confuser hydraulic diamater)", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": try to set Din (confuser inlet diameter) < D0 (confuser hydraulic diamater)"));
		}
		if (G.at(5) < 0.0)
		{
			err += procInvalidValue("R0 (confuser curve radius) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set R0 (confuser curve radius) < 0.0"));
		}
	}

	return err;
}

void CylindricalConfuserCurveDirect::evaluateDirect()
{
	A_ = M_PI * pow(0.5 * D0_, 2.0);
	A1_ = M_PI * pow(0.5 * D1_, 2.0);
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
			FrictionPart_.evaluate();
			lf_ = FrictionPart_.getRelFrictionCoeff();

			// diagram 5-23
			diagram523();
		}
	}
}

void hydrocalc::CylindricalConfuserCurveDirect::diagram523()
{
	diagram_ = "5-23";

	real n0c = A_ / A1_;
	// calculate F with approximation
	real inputE[2] = { std::max(0.25, std::min(0.64, n0c)), std::max(0.0, std::min(2.0, R0_ / D0_)) };
	E523Calc(inputE, 1, &CSIlf_, 1, NULL, 0, 0);

	CSIlr_ = 0.0;
	CSI_ = CSIlr_ + CSIlf_;
}

HydraulicResistance* CylindricalConfuserCurveDirect::copy() const
{
	return new CylindricalConfuserCurveDirect(
		Re_, 
		{
			rou_,
			D0_,
			L0_,
			L_,
			D1_,
			R0_
		},
		name_,
		vis_
	);
}

void CylindricalConfuserCurveDirect::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L_ = err;
		L0_ = err;
		D1_ = err;
		R0_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L0_ = G.at(2);
		L_ = G.at(3);
		D1_ = G.at(4);
		R0_ = G.at(5);
	}

	FrictionPart_.setGeometry({ rou_, D0_, L_ });
}

void hydrocalc::CylindricalConfuserCurveDirect::evaluate()
{
	real err = procNonExixtantFunc("evaluate", ExceptionNonExistentFunction("Try to call function ""evaluate"", forbidden for direct curve confuser element: " + name_));

	return void();
}

void CylindricalConfuserCurveDirect::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		L_,
		D1_,
		R0_,
		A_,
		A1_
	};
}
