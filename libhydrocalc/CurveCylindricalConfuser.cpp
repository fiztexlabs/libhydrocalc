#include <pch.h>
#include <HydraulicResistances/CurveCylindricalConfuser.h>
#include <HydraulicResistances/CurveCylindricalDiffuser.h>
#include <HydraulicResistances/approximations/E523.h>
#include <math/mathlib.h>

CurveCylindricalDiffuser* CurveCylindricalConfuser::createDiffuser()
{
	return new CurveCylindricalDiffuser(name_ + "_negative_flow", abs(Re_),
		{ rou_,D0_,Lc_,1.e-6,D1_,R0_ }, false);
}

void CurveCylindricalConfuser::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}

		if (Re_ < 1.e5)
		{
			std::cerr << "%warn Re less than 1e5 in the element " << id_ << " (" << name_ << ") (diagram 5-23)\n";
		}
		if (L0_ == 0.0)
		{
			std::cerr << "%warn L0 equals to 0 in the element " << id_ << " (" << name_ << ") (diagram 5-23)\n";
		}
	}
}

void CurveCylindricalConfuser::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
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
	if (G[5] <= 0.0)
	{
		std::cerr << "%err invalid value of G, curve radius R0 (G[5]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void CurveCylindricalConfuser::calculateElement()
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
			// call diffuser calculateElement()
			InvertConfuser->setGeometry({ rou_,D0_,Lc_,1.e-6,D1_ });
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
			// chek values
			errorHandling();

			A_ = M_PI * pow(0.5 * D0_, 2.0);
			A1_ = M_PI * pow(0.5 * D1_, 2.0);
			relRou_ = rou_ / D0_;

			FrictionPart.setGeometry({ rou_,D0_,Lc_ });
			FrictionPart.setRe(Re);
			if (!autocalc)
			{
				FrictionPart.calculateElement();
			}

			lf_ = FrictionPart.getRelFrictionCoeff();

			// diagram 5-23
			diagram_ = "5-23";

			HSReal n0c = A_ / A1_;
			// calculate F with approximation
			HSReal inputE[2] = { max(0.25, min(0.64, n0c)), max(0.0, min(2.0, R0_ / D0_)) };
			E523Calc(inputE, 1, &CSIlf_, 1, NULL, 0, 0);

			CSIlr_ = 0.0;
			CSI_ = CSIlr_ + CSIlf_;
		}
	}
	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* CurveCylindricalConfuser::copy() const
{
	return new CurveCylindricalConfuser(name_, Re_,
		{
			rou_,
			D0_,
			L0_,
			Lc_,
			D1_,
			R0_
		}
	);
}

void CurveCylindricalConfuser::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != L0_) || (G[3] != Lc_) || (G[4] != D1_) || (G[5] != R0_))
	{
		rou_ = G[0];
		D0_ = G[1];
		L0_ = G[2];
		Lc_ = G[3];
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

void CurveCylindricalConfuser::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		L0_,
		Lc_,
		D1_,
		R0_,
		A_,
		A1_
	};
}

HSReal CurveCylindricalConfuser::getLength()
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

void CurveCylindricalConfuser::setLength(const HSReal L)
{
	Lc_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
