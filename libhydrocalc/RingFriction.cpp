#include <pch.h>
#include "RingFriction.h"
#include <math/mathlib.h>
#include <HydraulicResistances/approximations/KN27.h>
#include <HydraulicResistances/approximations/KE27.h>

void RingFriction::errorHandling()
{
	errorHandling(Re_, { rou_,d_ext_,d_int_,exc_,L_ });
}

void RingFriction::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (G.size() < 5)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 5 in the element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (flagHandleWarnings)
	{
		if (G.size() > 5)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 5 in the element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G[0] < 0.0)
	{
		std::cerr << "%err invalid value of G, roughness rou (G[0]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] <= 0.0)
	{
		std::cerr << "%err invalid value of G, external diameter of the ring channel  (G[1]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[2] <= 0.0)
	{
		std::cerr << "%err invalid value of G, internal diameter of the ring channel  (G[2]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] < G[2])
	{
		std::cerr << "%err invalid value of G, external diameter of the ring channel must be greater than internal diameter (G[1] must be > G[2]) in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[3] < 0.0)
	{
		std::cerr << "%err invalid value of G, excentric of the ring channel (G[3]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[4] < 0.0)
	{
		std::cerr << "%err invalid value of G, length of channel L0 (G[4]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}

	if (Re_ < 0.0)
	{
		if (flagHandleWarnings)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
	}
}

void RingFriction::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	// chek values
	errorHandling();
	// direction independent
	HSReal Re = abs(Re_);

	A_ = M_PI * (pow(0.5 * d_ext_, 2.0) - pow(0.5 * d_int_, 2.0));
	relRou_ = rou_ / D0_;

	if (math::isEqual<HSReal, HSReal>(Re, static_cast<HSReal>(0.0)))
	{
		CSI_ = 0.0;
		CSIlf_ = 0.0;
		CSIlr_ = 0.0;
		lf_ = 0.0;
	}
	else
	{
		FrictionPart.setGeometry({ rou_,D0_,0.0 });
		FrictionPart.setRe(Re);
		if (!autocalc)
		{
			FrictionPart.calculateElement();
		}
		HSReal lf_t = FrictionPart.getRelFrictionCoeff();

		diagram_ = "2-7";

		HSReal kn_conc = static_cast <HSReal>(1.0); 
		HSReal dD = d_int_ / d_ext_;
		if (math::isEqual<HSReal, HSReal>(exc_, static_cast<HSReal>(0.0)))
		{
			// concentric ring channel
			if (Re <= 2.e3)
			{
				// laminar
				kn_conc = (1.0 - pow(dD, 2.0)) / (1.0 + pow(dD, 2.0) + (1.0 - pow(dD, 2.0)) / log(dD));
			}
			else
			{
				// turbulent
				// calculate kn with approximation
				HSReal inputKN[2] = { max(1.e5, min(1.e8, Re)), dD };
				KN27Calc(inputKN, 1, &kn_conc, 1, NULL, 0, 0);
			}
			lf_ = lf_t * kn_conc;
		}
		else
		{
			// excentric
			// relative excentric
			HSReal exc_rel = 2.0 * exc_ / D0_;
			HSReal kn_exc = 0.0;
			if (Re <= 2.e3)
			{
				// laminar
				// calculate B1 with approximation 
				HSReal B1 = -4.390059731993820E+01 * pow(dD, 6.0) + 1.439031278751790E+02 * pow(dD, 5.0)
					- 1.854757497515520E+02 * pow(dD, 4.0) + 1.204940348779780E+02 * pow(dD, 3.0)
					- 4.322343308362170E+01 * pow(dD, 2.0) + 9.680854071179060E+00 * dD + 1.635598329528420E-03;

				// as for concentric
				kn_conc = (1.0 - pow(dD, 2.0)) / (1.0 + pow(dD, 2.0) + (1.0 - pow(dD, 2.0)) / log(dD));
				// kn for excentric
				kn_exc = kn_conc * B1;
			}
			else
			{
				// turbulent
				// calculate ke with approximation
				HSReal inputKE[2] = { max(0.0, min(1.0, exc_rel)), max(0.5, min(0.7, dD)) };
				HSReal ke_exc = 0.0;
				KE27Calc(inputKE, 1, &ke_exc, 1, NULL, 0, 0);

				// calculate kn as for concentric
				HSReal inputKN[2] = { max(1.e5, min(1.e8, Re)), dD };
				KN27Calc(inputKN, 1, &kn_conc, 1, NULL, 0, 0);

				kn_exc = ke_exc * kn_conc;

				lf_ = lf_t * kn_exc;
			}

		}
		CSIlf_ = lf_ * (L_ / D0_);
		CSIlr_ = 0.0;
		CSI_ = CSIlf_ + CSIlr_;
	}

	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* RingFriction::copy() const
{
	return new RingFriction(name_, Re_,
		{
			rou_,
			d_ext_,
			d_int_,
			exc_,
			L_
		}
	);
}

void RingFriction::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != d_ext_) || (G[2] != d_int_) || (G[3] != exc_) || (G[4] != L_))
	{
		rou_ = G[0];
		d_ext_ = G[1];
		d_int_ = G[2];
		exc_ = G[3];
		L_ = G[4];
		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void RingFriction::getGeometry(std::vector<HSReal>& G)
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

HSReal RingFriction::getLength()
{
	if (L_ > 0.0)
	{
		return L_;
	}
	else
	{
		return 1.e-6;
	}
}

void RingFriction::setLength(const HSReal L)
{
	L_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
