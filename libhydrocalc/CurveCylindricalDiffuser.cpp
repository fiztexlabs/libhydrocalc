#include <pch.h>
#include <HydraulicResistances/CurveCylindricalDiffuser.h>
#include <HydraulicResistances/CurveCylindricalConfuser.h>
#include <math/mathlib.h>

CurveCylindricalConfuser* CurveCylindricalDiffuser::createConfuser()
{
	return new CurveCylindricalConfuser(name_ + "_negative_flow", abs(Re_),
		{ rou_,D0_,L1_,Ld_,D1_,R0_ }, false);
}

void CurveCylindricalDiffuser::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
		if (Re_ < 1.e5)
		{
			std::cerr << "%warn Re less than 1e5 in the element " << id_ << " (" << name_ << ") (diagram 5-8)\n";
		}
		if (L1_ == 0.0)
		{
			std::cerr << "%warn L1 equals to 0 in the element " << id_ << " (" << name_ << ") (diagram 5-8)\n";
		}
	}
}

void CurveCylindricalDiffuser::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
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
		std::cerr << "%err invalid value of G, length of diffuser Ld (G[3]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
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
	if (G[5] <= 0.0)
	{
		std::cerr << "%err invalid value of G, curve radius R0 (G[5]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void CurveCylindricalDiffuser::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	HSReal Re = Re_;

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
			InvertDiffuser->setGeometry({ rou_,D0_,L1_,Ld_,D1_,R0_ });
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
		else
		{
			// chek values
			errorHandling();

			A_ = M_PI * pow(0.5 * D0_, 2.0);
			A1_ = M_PI * pow(0.5 * D1_, 2.0);
			relRou_ = rou_ / D0_;

			HSReal n1d = A1_ / A_;

			FrictionPart.setGeometry({ rou_,D0_,Ld_ });
			FrictionPart.setRe(Re);
			if (!autocalc)
			{
				FrictionPart.calculateElement();
			}

			lf_ = FrictionPart.getRelFrictionCoeff();

			if (flagHandleWarnings)
			{
				if (n1d > 0.9)
				{
					std::cerr << "%warn F0/F1 more than 0.9 in the element " << id_ << " (" << name_ << ") (diagram 5-8)\n";
				}
				if (n1d < 0.9)
				{
					std::cerr << "%warn F0/F1 less than 0.1 degree in the element " << id_ << " (" << name_ << ") (diagram 5-8)\n";
				}
			}

			// diagram 5-8
			diagram_ = "5-8";
			HSReal sigm0 = 1.43 - 1.3 * (A_ / A1_);
			HSReal d1 = pow(1.0 - (A_ / A1_), 2.0);
			HSReal f0 = 0.0;

			HSReal LD = Ld_ / D0_;
			if (LD >= 4.0)
			{
				f0 = 0.37;
			}
			else
			{
				f0 = 0.0560606060606061 * pow(LD, 2.0) - 0.365909090909091 * LD + 0.966363636363635;
			}

			CSIlf_ = sigm0 * d1 * f0;
			CSIlr_ = 0.0;
			CSI_ = CSIlr_ + CSIlf_;
		}
	}

	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* CurveCylindricalDiffuser::copy() const
{
	return new CurveCylindricalDiffuser(name_, Re_,
		{
			rou_,
			D0_,
			Ld_,
			L1_,
			D1_,
			R0_
		}
	);
}

void CurveCylindricalDiffuser::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != Ld_) ||	(G[3] != L1_) || (G[4] != D1_) || (G[5] != R0_))
	{
		rou_ = G[0];
		D0_ = G[1];
		Ld_ = G[2];
		L1_ = G[3];
		D1_ = G[4];
		R0_ = G[5];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void CurveCylindricalDiffuser::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		Ld_,
		L1_,
		D1_,
		A_,
		A1_
	};
}

HSReal CurveCylindricalDiffuser::getLength()
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

void CurveCylindricalDiffuser::setLength(const HSReal L)
{
	Ld_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
