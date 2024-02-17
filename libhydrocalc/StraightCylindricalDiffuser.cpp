#include <pch.h>
#include <HydraulicResistances/StraightCylindricalDiffuser.h>
#include <HydraulicResistances/StraightCylindricalConfuser.h>
#include <HydraulicResistances/approximations\F52.h>
#include <HydraulicResistances/approximations\E59.h>
#include <math/mathlib.h>

StraightCylindricalConfuser* StraightCylindricalDiffuser::createConfuser()
{
	return new StraightCylindricalConfuser(name_ + "_negative_flow", abs(Re_),
		{ rou_,D0_,L1_,Ld_,D1_,alpha_ }, false);
}

void StraightCylindricalDiffuser::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
		if (alpha_ < 3)
		{
			std::cerr << "%warn diffuser angle less than 3 degree in the element " << id_ << " (" << name_ << ")\n";
		}
	}
}

void StraightCylindricalDiffuser::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (flagHandleWarnings)
	{
		if (G.size() > 9)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 9 in the element " << id_ << " (" << name_ << ")\n";
		}
		if (G[8] < 3)
		{
			std::cerr << "%warn diffuser angle less than 3 degree in the element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G.size() < 9)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 9 in the element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (G[0] < 0.0)
	{
		std::cerr << "%err invalid value of G, roughness rou (G[0]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] <= 0.0)
	{
		std::cerr << "%err invalid value of G, diameter of channel D0 (G[1]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[2] < 1.0)
	{
		std::cerr << "%err invalid value of G, turbulence intensity I (G[2]) must be >= 1.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[3] < 0.0)
	{
		std::cerr << "%err invalid value of G, length of inlet section L0 (G[3]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[4] <= 0.0)
	{
		std::cerr << "%err invalid value of G, length of diffuser Ld (G[4]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[5] < 0.0)
	{
		std::cerr << "%err invalid value of G, length of outlet section L1 (G[5]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[6] < 0.0)
	{
		std::cerr << "%err invalid value of G, diameter of diffuser outlet Dout (G[6]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] / G[6] > 1.0)
	{
		std::cerr << "%err invalid value of G, relation D0/Dout must be <= 1.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[7] < 0.0)
	{
		std::cerr << "%err invalid value of G, hydraulic diameter of outlet section D1 (G[7]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[8] > 180.0)
	{
		std::cerr << "%err invalid value of G, diffuser angle alpha (G[8]) more than 180 [deg] inthe element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[8] < 0.0)
	{
		std::cerr << "%err invalid value of G, diffuser angle alpha (G[8]) less than 0 [deg] inthe element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void StraightCylindricalDiffuser::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	HSReal Re = Re_;

	// chek values
	errorHandling();

	A_ = M_PI * pow(0.5 * D0_, 2.0);
	A1_ = M_PI * pow(0.5 * D1_, 2.0);
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
		if (Re < 0.0)
		{
			// call confuser calculateElement()
			if (D1_ == Dout_)
			{
				InvertDiffuser->setGeometry({ rou_,D0_,L1_,Ld_,D1_,alpha_ });
				InvertDiffuser->setRe(abs(Re));
				if (!autocalc)
				{
					InvertDiffuser->calculateElement();
				}

				InvertDiffuser->getDiagram(diagram_);
				lf_ = InvertDiffuser->getRelFrictionCoeff();
				CSIlf_ = InvertDiffuser->getFrictionPartCoeff();
				CSIlr_ = InvertDiffuser->getGeometryPartCoeff();
				CSI_ = InvertDiffuser->getLocalResistanceCoeff();
			}
			// if diagram 5-9 call confuser + suddenly expansion
			else
			{

			}
		}
		else
		{
			HSReal n1d = A1_ / A_;

			FrictionPart.setGeometry({ rou_,D0_,Ld_ });
			FrictionPart.setRe(Re);
			if (!autocalc)
			{
				FrictionPart.calculateElement();
			}

			lf_ = FrictionPart.getRelFrictionCoeff();

			// if angle = 0, diffuser reduced to friction
			if (alpha_ == 0.0)
			{
				CSIlf_ = FrictionPart.getFrictionPartCoeff();
				CSIlr_ = FrictionPart.getGeometryPartCoeff();
				CSI_ = FrictionPart.getLocalResistanceCoeff();
				return void();
			}

			if (D1_ == Dout_)
			{
				// diagram 5-2 (turbulent)
				if (Re > 50.0)
				{
					diagram_ = "5-2";

					HSReal csi_lf1 = (lf_ / (8.0 * sin((0.5 * alpha_) / (180.0 / M_PI)))) * (1.0 - (1.0 / n1d));

					HSReal xd = L1_ / D0_;

					HSReal avgXd = log(1.0 + 2.0 * xd * tan((0.5 * alpha_) / (180.0 / M_PI)))
						/ (2.0 * tan((0.5 * alpha_) / (180.0 / M_PI)));

					CSIlf_ = csi_lf1 * (1.0 + (0.5 / pow(1.5, avgXd)));

					if (flagHandleWarnings)
					{
						// check Re for diagram 5-2
						if (Re < 0.5e5)
						{
							std::cerr << "%warn Re = " << Re << " less than 0.5e5 in the element " << id_ << " (" << name_ << ") (diagram 5-2)\n";
						}
						if (Re > 6.e5)
						{
							std::cerr << "%warn Re = " << Re << " more than 6e5 in the element " << id_ << " (" << name_ << ") (diagram 5-2)\n";
						}
					}

					// constraint for Re in calculations of hit coefficient F
					HSReal Re1 = max(0.5e5, min(Re, 6.e5));
					// calculate F with approximation
					HSReal F = 0.0;
					HSReal inputF[2] = { alpha_, Re1 };
					F52Calc(inputF, 1, &F, 1, NULL, 0, 0);

					HSReal csi_exp = F * pow((1.0 - (1.0 / n1d)), 1.92);

					HSReal ad = 0.924 / (1.0 + 1.3e-5 * pow(alpha_, 3.14));
					HSReal bd = (0.3 + 1.55 * pow(1.1, -alpha_)) / (1.0 + 1.03e-8 * pow(L0_ / D0_, 7.5));
					long double cd = 1.05 / (1.0 + 2.3e-62 * pow(Re, 11));

					HSReal csi_turb = 0.044 * pow(0.345 * alpha_, ad) * (1.0 - pow(0.2 * n1d + 0.8, -3.82)) * pow(0.154 * (L0_ / D0_), bd)
						* pow(2.31e-6 * Re + 0.2 + 2.54 * pow((1.0 + 0.081 * alpha_), -1.51), static_cast<HSReal>(cd));

					CSIlr_ = csi_exp + csi_turb;

					CSI_ = CSIlf_ + CSIlr_;
				}
				// diagram 5-7 (laminar)
				else
				{
					diagram_ = "5-7";

					CSIlr_ = 0.0;

					HSReal A = (20.0 * pow(n1d, 0.33)) / pow(tan((alpha_) / (180.0 / M_PI)), 0.75);
					CSIlf_ = A / Re;

					CSI_ = CSIlf_ + CSIlr_;
				}
			}
			// diagram 5-9
			else
			{
				diagram_ = "5-9";

				// calculate CSI with approximation
				HSReal np = (M_PI * pow(0.5 * Dout_, 2.0)) / A_;
				HSReal inputE[2] = { max(1.5, min(20.0, np)), max(0.5, min(14.0, Ld_ / D0_)) };
				E59Calc(inputE, 1, &CSIlr_, 1, NULL, 0, 0);
			}

		}
	}

	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* StraightCylindricalDiffuser::copy() const
{
	return new StraightCylindricalDiffuser(name_, Re_, { rou_, D0_, I_, L0_, Ld_, L1_, Dout_, D1_, alpha_ });
}

void StraightCylindricalDiffuser::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != I_) || (G[3] != L0_) || (G[4] != Ld_) ||
		(G[5] != L1_) || (G[6] != Dout_) || (G[7] != D1_) || (G[8] != alpha_))
	{
		rou_ = G[0];
		D0_ = G[1];
		I_ = G[2];
		L0_ = G[3];
		Ld_ = G[4];
		L1_ = G[5];
		Dout_ = G[6];
		D1_ = G[7];
		alpha_ = G[8];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void StraightCylindricalDiffuser::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		Ld_,
		L1_,
		Dout_,
		D1_,
		alpha_,
		A_,
		A1_
	};
}

HSReal StraightCylindricalDiffuser::getLength()
{
	if (Ld_ > 0.0)
	{
		return Ld_;
	}
	else
	{
		return 1.e-6;
	}
}

void StraightCylindricalDiffuser::setLength(const HSReal L)
{
	Ld_ = L;

	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
