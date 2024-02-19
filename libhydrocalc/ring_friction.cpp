#include <libhydrocalc/ring_friction.h>
#include <libhydrocalc/approximations/ke27.h>
#include <libhydrocalc/approximations/kn27.h>
#include <libmath/boolean.h>
#include <cmath>
#include <algorithm>

using namespace hydrocalc;

real RingFriction::checkGeometry(const std::vector<real>& G)
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
			err += procInvalidValue("D1 (external diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D1 (external diameter) <= 0.0"));
		}
		if (G.at(2) <= 0.0)
		{
			err += procInvalidValue("D2 (internal diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D2 (internal diameter) <= 0.0"));
		}
		if (G.at(1) <= G.at(2))
		{
			err += procInvalidValue("D1 (external diameter) <= D2 (internal diameter)", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D1 (external diameter) <= D2 (internal diameter)"));
		}
		if (G.at(3) < 0.0)
		{
			err += procInvalidValue("E (ring excentric) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set E (ring excentric) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("L (element length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L (element length) < 0.0"));
		}
	}

	return err;
}

void hydrocalc::RingFriction::diagram27()
{
	diagram_ = "2-7";

	real Re = std::abs(Re_);

	FrictionPart_.evaluate();
	real lf_t = FrictionPart_.getRelFrictionCoeff();
	
	real kn_conc = static_cast <real>(1.0);
	real dD = d_int_ / d_ext_;
	if (math::isEqual<real, real>(exc_, static_cast<real>(0.0)))
	{
		// concentric ring channel
		if (Re <= 2.e3)
		{
			// lastd::minar
			kn_conc = (1.0 - std::pow(dD, 2.0)) / (1.0 + std::pow(dD, 2.0) + (1.0 - std::pow(dD, 2.0)) / log(dD));
		}
		else
		{
			// turbulent
			// calculate kn with approximation
			real inputKN[2] = { std::max(1.e5, std::min(1.e8, Re)), dD };
			KN27Calc(inputKN, 1, &kn_conc, 1, NULL, 0, 0);
		}
		lf_ = lf_t * kn_conc;
	}
	else
	{
		// excentric
		// relative excentric
		real exc_rel = 2.0 * exc_ / D0_;
		real kn_exc = 0.0;
		if (Re <= 2.e3)
		{
			// lastd::minar
			// calculate B1 with approximation 
			real B1 = -4.390059731993820E+01 * std::pow(dD, 6.0) + 1.439031278751790E+02 * std::pow(dD, 5.0)
				- 1.854757497515520E+02 * std::pow(dD, 4.0) + 1.204940348779780E+02 * std::pow(dD, 3.0)
				- 4.322343308362170E+01 * std::pow(dD, 2.0) + 9.680854071179060E+00 * dD + 1.635598329528420E-03;

			// as for concentric
			kn_conc = (1.0 - std::pow(dD, 2.0)) / (1.0 + std::pow(dD, 2.0) + (1.0 - std::pow(dD, 2.0)) / log(dD));
			// kn for excentric
			kn_exc = kn_conc * B1;
		}
		else
		{
			// turbulent
			// calculate ke with approximation
			real inputKE[2] = { std::max(0.0, std::min(1.0, exc_rel)), std::max(0.5, std::min(0.7, dD)) };
			real ke_exc = 0.0;
			KE27Calc(inputKE, 1, &ke_exc, 1, NULL, 0, 0);

			// calculate kn as for concentric
			real inputKN[2] = { std::max(1.e5, std::min(1.e8, Re)), dD };
			KN27Calc(inputKN, 1, &kn_conc, 1, NULL, 0, 0);

			kn_exc = ke_exc * kn_conc;

			lf_ = lf_t * kn_exc;
		}

	}
	CSIlf_ = lf_ * (L_ / D0_);
	CSIlr_ = 0.0;
	CSI_ = CSIlf_ + CSIlr_;
}

void RingFriction::evaluate()
{
	A_ = M_PI * (std::pow(0.5 * d_ext_, 2.0) - std::pow(0.5 * d_int_, 2.0));
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
		real Re = abs(Re_);

		A_ = M_PI * (std::pow(0.5 * d_ext_, 2.0) - std::pow(0.5 * d_int_, 2.0));
		relRou_ = rou_ / D0_;

		if (math::isEqual<real, real>(Re, static_cast<real>(0.0)))
		{
			CSI_ = CurrentSettings_.MAX_CSI;
			CSIlf_ = 0.0;
			CSIlr_ = CurrentSettings_.MAX_CSI;
			lf_ = 0.0;
		}
		else
		{
			// diagram 2-7
			diagram27();
		}
	}
}

HydraulicResistance* RingFriction::copy() const
{
	return new RingFriction(
		Re_,
		{
			rou_,
			d_ext_,
			d_int_,
			exc_,
			L_
		},
		name_
	);
}

void RingFriction::setGeometry(const std::vector<real>& G)
{
	// check inputs
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		d_ext_ = err;
		d_int_ = err;
		exc_ = err;
		L_ = err;
	}
	else
	{
		rou_ = G.at(0);
		d_ext_ = G.at(1);
		d_int_ = G.at(2);
		exc_ = G.at(3);
		L_ = G.at(4);
		D0_ = d_ext_ - d_int_;
	}
}

void RingFriction::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		d_ext_,
		d_int_,
		exc_,
		L_,
		A_
	};
}
