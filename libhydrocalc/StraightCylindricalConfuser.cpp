#include <pch.h>
#include <HydraulicResistances/StraightCylindricalConfuser.h>
#include <HydraulicResistances/StraightCylindricalDiffuser.h>
#include <math/mathlib.h>

StraightCylindricalDiffuser* StraightCylindricalConfuser::createDiffuser()
{
	return new StraightCylindricalDiffuser(name_ + "_negative_flow", abs(Re_),
		{ rou_,D0_,1.0,1.e-6,Lc_,L0_,D1_,D1_,alpha_ }, false);
}

void StraightCylindricalConfuser::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
	}
}

void StraightCylindricalConfuser::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (flagHandleWarnings)
	{
		if (G.size() > 6)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 6 in the element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G.size() < 6)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 6 in the element " << id_ << " (" << name_ << ")\n";
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
	if (G[2] < 0.0)
	{
		std::cerr << "%err invalid value of G, length of outlet section L1 (G[2]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[3] <= 0.0)
	{
		std::cerr << "%err invalid value of G, length of confuser Lc (G[3]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[4] < 0.0)
	{
		std::cerr << "%err invalid value of G, hydraulic diameter of outlet section D1 (G[4]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] / G[4] > 1.0)
	{
		std::cerr << "%err invalid value of G, relation D0/D1 must be <= 1.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[5] > 180.0)
	{
		std::cerr << "%err invalid value of G, confuser angle alpha (G[5]) more than 180 [deg] in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[5] < 0.0)
	{
		std::cerr << "%err invalid value of G, confuser angle alpha (G[5]) less than 0 [deg] in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void StraightCylindricalConfuser::calculateElement()
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
			// call diffuser calculateElement()
			InvertConfuser->setGeometry({ rou_,D0_,1.0,1.e-6,Lc_,L0_,D1_,D1_,alpha_ });
			InvertConfuser->setRe(abs(Re));
			if (!autocalc)
			{
				InvertConfuser->calculateElement();
			}

			InvertConfuser->getDiagram(diagram_);
			lf_ = InvertConfuser->getRelFrictionCoeff();
			CSIlf_ = InvertConfuser->getFrictionPartCoeff();
			CSIlr_ = InvertConfuser->getGeometryPartCoeff();
			CSI_ = InvertConfuser->getLocalResistanceCoeff();
		}
		else
		{
			HSReal n0d = A_ / A1_;

			FrictionPart.setGeometry({ rou_,D0_,Lc_ });
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

			// diagram 5-23 (turbulent)
			if (Re > 50.0)
			{
				diagram_ = "5-23";

				if (flagHandleWarnings)
				{
					// check Re for diagram 5-23
					if (Re < 1.e5)
					{
						std::cerr << "%warn Re = " << Re << " less than 1e5 in the element " << id_ << " (" << name_ << ") (diagram 5-23)\n";
					}
				}

				HSReal csi_lf1 = (lf_ / (8.0 * sin((0.5 * alpha_) / (180.0 / M_PI)))) * (1.0 - pow(n0d, 2.0));

				HSReal xd = L0_ / D0_;

				HSReal avgXd = log(1.0 + 2.0 * xd * tan((0.5 * alpha_) / (180.0 / M_PI)))
					/ (2.0 * tan((0.5 * alpha_) / (180.0 / M_PI)));

				CSIlf_ = csi_lf1 * (1.0 + (0.5 / pow(1.5, avgXd)));

				HSReal ap = 0.01745 * alpha_;
				CSIlr_ = (-0.0125 * pow(n0d, 4.0) + 0.0224 * pow(n0d, 3.0) - 0.00723 * pow(n0d, 3.0) + 0.00444 * n0d - 0.00745)
					* (pow(ap, 3.0) - 2.0 * M_PI * pow(ap, 2.0) - 10.0 * ap);

				CSI_ = CSIlf_ + CSIlr_;
			}
			// diagram 5-24 (laminar)
			else
			{
				diagram_ = "5-24";

				CSIlr_ = 0.0;

				HSReal A = 20.5 / (pow(tan((alpha_) / (180.0 / M_PI)), 0.75) * pow(n0d, 0.5));
				CSIlf_ = A / Re;

				CSI_ = CSIlf_ + CSIlr_;

			}
		}
	}

	calculated = 1;
	changed = 0;



}

IBaseHydraulicResistance* StraightCylindricalConfuser::copy() const
{
	return new StraightCylindricalConfuser(name_, Re_, 
		{
		rou_,
		D0_,
		L0_,
		Lc_,
		D1_,
		alpha_ 
		}
	);
}

void StraightCylindricalConfuser::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != L0_) || (G[3] != Lc_) 
		|| (G[4] != D1_) || (G[4] != alpha_))
	{
		rou_ = G[0];
		D0_ = G[1];
		L0_ = G[2];
		Lc_ = G[3];
		D1_ = G[4];
		alpha_ = G[5];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void StraightCylindricalConfuser::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		Lc_,
		D1_,
		alpha_,
		A_,
		A1_
	};
}

HSReal StraightCylindricalConfuser::getLength()
{
	if (Lc_ > 0.0)
	{
		return Lc_;
	}
	else
	{
		return 1.e-6;
	}
}

void StraightCylindricalConfuser::setLength(const HSReal L)
{
	Lc_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
