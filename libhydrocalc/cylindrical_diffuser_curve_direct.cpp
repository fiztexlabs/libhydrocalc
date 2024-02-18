#include <libhydrocalc/cylindrical_diffuser_curve_direct.h>
#include <libmath/boolean.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real CylindricalDiffuserCurveDirect::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) < 0.0)
		{
			err += procInvalidValue("rou (roughness) < 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set rou (roughness) < 0.0"));
		}
		if (G.at(1) <= 0.0)
		{
			err += procInvalidValue("D0 (diffuser hydraulic diameter) <= 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set D0 (diffuser hydraulic diameter) < 0.0"));
		}
		if (G.at(3) < 0.0)
		{
			err += procInvalidValue("L1 (diffuser outlet section length) < 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set L1 (diffuser outlet section length) < 0.0"));
		}
		if (G.at(2) < 0.0)
		{
			err += procInvalidValue("L (diffuser length) < 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set L (diffuser length) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("Dout (diffuser outlet diameter) < 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set Dout (diffuser outlet diameter) < 0.0"));
		}
		if (G.at(4) < G.at(1))
		{
			err += procGeometryOutOfRange("Dout (diffuser outlet diameter) < D0 (diffuser hydraulic diamater)", ExceptionGeometryOutOfRange("Curve cylindrical diffuser element " + name_ + ": try to set Dout (diffuser outlet diameter) < D0 (diffuser hydraulic diamater)"));
		}
		if (G.at(5) < 0.0)
		{
			err += procInvalidValue("R0 (diffuser curve radius) < 0.0", ExceptionInvalidValue("Curve cylindrical diffuser element " + name_ + ": try to set R0 (diffuser curve radius) < 0.0"));
		}
	}

	return err;
}

void CylindricalDiffuserCurveDirect::evaluateDirect()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);
	A1_ = M_PI * std::pow(0.5 * D1_, 2.0);
	relRou_ = rou_ / D0_;

	real reversed = checkReversedFlow("Re < 0.0", ExceptionReversedFlow("reversed flow in the curve cylindrical diffuser element " + name_));

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

			// diagram 5-8
			diagram58();
		}
	}
}

void hydrocalc::CylindricalDiffuserCurveDirect::diagram58()
{
	diagram_ = "5-8";

	real Re = std::abs(Re_);

	real n1d = A1_ / A_;

	real err{ 0.0 };

	if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
	{
		if (n1d > 0.9)
		{
			err += procGeometryOutOfRange("Aout/Ahydr = " + std::to_string(n1d) + " > 0.9", ExceptionGeometryOutOfRange("Curve cylindrical diffuser element " + name_ + ": R0/D0 < 0.5"));
		}
		if (n1d < 0.1)
		{
			err += procGeometryOutOfRange("Aout/Ahydr = " + std::to_string(n1d) + " < 0.1", ExceptionGeometryOutOfRange("Curve cylindrical diffuser element " + name_ + ": L0/D0 < 10.0"));
		}

		if (std::isnan(err))
		{
			CSIlf_ = err;
			CSIlr_ = err;
			CSI_ = err;

			return void();
		}
	}

	real sigm0 = 1.43 - 1.3 * (A_ / A1_);
	real d1 = std::pow(1.0 - (A_ / A1_), 2.0);
	real f0 = 0.0;

	real LD = L_ / D0_;
	if (LD >= 4.0)
	{
		f0 = 0.37;
	}
	else
	{
		f0 = 0.0560606060606061 * std::pow(LD, 2.0) - 0.365909090909091 * LD + 0.966363636363635;
	}

	CSIlf_ = sigm0 * d1 * f0;
	CSIlr_ = 0.0;
	CSI_ = CSIlr_ + CSIlf_;
}

HydraulicResistance* CylindricalDiffuserCurveDirect::copy() const
{
	return new CylindricalDiffuserCurveDirect(
		Re_,
		{
			rou_,
			D0_,
			L_,
			L1_,
			D1_,
			R0_
		},
		name_
	);
}

void CylindricalDiffuserCurveDirect::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L_ = err;
		L1_ = err;
		D1_ = err;
		R0_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L_ = G.at(2);
		L1_ = G.at(3);
		D1_ = G.at(4);
		R0_ = G.at(5);
	}

	FrictionPart_.setGeometry({ rou_, D0_, L_ });
}

void hydrocalc::CylindricalDiffuserCurveDirect::evaluate()
{
	real err = procNonExixtantFunc("evaluate", ExceptionNonExistentFunction("Try to call function ""evaluate"", forbidden for direct curve diffuser element: " + name_));

	return void();
}

void CylindricalDiffuserCurveDirect::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L_,
		L1_,
		D1_,
		A_,
		A1_
	};
}
