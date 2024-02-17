#include <pch.h>
#include <HydraulicResistances/CylindricalFriction.h>
#include <math/mathlib.h>

void CylindricalFriction::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	// chek values
	errorHandling();
	// direction independent
	HSReal Re = abs(Re_);

	A_ = M_PI * pow(0.5 * D0_, 2.0);
	relRou_ = rou_ / D0_;

	if (math::isEqual<HSReal, HSReal>(Re, static_cast<HSReal>(0.0)))
	{
		lf_ = 0.0;
		CSI_ = 0.0;
		CSIlr_ = 0.0;
		CSIlf_ = 0.0;
	}
	else
	{
		// diagram 2-1
		if (rou_ == 0.0)
		{
			diagram_ = "2-1";
			relRou_ = 0.0;
			// laminar
			if (Re <= 2000.0)
			{
				lf_ = 64.0 / Re;
			}
			// transient (approximation)
			if ((Re > 2000.0) && (Re < 4000.0))
			{
				lf_ = 7777777.77777767 * pow(Re, 2.0) - 364999.999999992 * Re + 6155.55555555541;
			}
			// turbulent
			if ((Re >= 4000.0) && (Re <= 100000.0))
			{
				lf_ = 0.3164 / pow(Re, 0.25);
			}
			// turbulent
			if (Re > 100000.0)
			{
				lf_ = pow((1.81 * log(Re) - 1.64), -2.0);
			}
		}
		else
		{
			// diagram 2-3
			diagram_ = "2-3";
			HSReal Re0 = 754.0 * exp(0.0065 / relRou_);
			HSReal Re1 = 1160.0 * pow((1.0 / relRou_), 0.11);
			HSReal Re2 = 2090.0 * pow((1.0 / relRou_), 0.0635);
			if ((Re > Re0) && (Re < Re1))
			{
				if (flagHandleWarnings)
				{
					// check relative roughness for diagram 2-3
					if (relRou_ < 0.007)
					{
						std::cerr << "%warn rou/D0 = " << relRou_ << " less than 0.007 in the element " << id_ << " (" << name_ << ") (diagram 2-3)\n";
					}
				}

				lf_ = 4.4 * pow(Re, -0.595) * exp(-0.00275 / relRou_);
			}
			if ((Re > Re1) && (Re < Re2))
			{
				HSReal l1 = 0.0;
				HSReal l2 = 0.0;
				if (relRou_ <= 0.007)
				{
					l1 = 0.032;
					l2 = 7.244 * pow(Re2, -0.643);
				}
				else
				{
					l1 = 0.0758 - (0.0109 / pow(relRou_, 0.286));
					l2 = 0.145 / pow(relRou_, -0.244);
				}

				lf_ = (l2 - l1) * exp(-pow(0.0017 * (Re2 - Re), 2.0)) + l1;
			}

			// diagram 2-4
			if (Re >= Re2)
			{
				diagram_ = "2-4";
				HSReal relRouLim = 15.0 / Re;
				if (rou_ < relRouLim * D0_)
				{
					if (Re <= 2000.0)
					{
						lf_ = 64.0 / Re;
					}
					// transient (approximation)
					if ((Re > 2000.0) && (Re < 4000.0))
					{
						lf_ = 7777777.77777767 * pow(Re, 2.0) - 364999.999999992 * Re + 6155.55555555541;
					}
					// turbulent
					if ((Re >= 4000.0) && (Re <= 100000.0))
					{
						lf_ = 0.3164 / pow(Re, 0.25);
					}
					// turbulent
					if (Re > 100000.0)
					{
						lf_ = pow((1.81 * log(Re) - 1.64), -2.0);
					}
				}
				else
				{
					if ((relRou_ >= 0.00008) && (relRou_ <= 0.0125))
					{
						lf_ = 0.11 * pow((relRou_ + (68 / Re)), 0.25);
					}
					else
					{
						lf_ = pow((2.0 * log((2.51 / (Re * sqrt(64.0 / Re))) + (relRou_ / 3.7))), -2.0);
					}
				}
			}
		}
		CSIlf_ = lf_ * (L_ / D0_);
		CSIlr_ = 0.0;
		CSI_ = CSIlf_ + CSIlr_;
	}
	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* CylindricalFriction::copy() const
{
	return new CylindricalFriction(name_, Re_,
		{
			rou_,
			D0_,
			L_
		}
	);
}

void CylindricalFriction::errorHandling()
{
	if (D0_ <= 0.0)
	{
		std::cerr << "%err invalid value of D0, diameter of channel (D0) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}

	if (L_ < 0.0)
	{
		std::cerr << "%err invalid value of L, length of channel (L) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
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

void CylindricalFriction::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (G.size() < 3)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 3 in the element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (G.size() > 3)
	{
		std::cerr << "%warn size of vector of geometry characteristics more than 3 in the element " << id_ << " (" << name_ << ")\n";
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
		std::cerr << "%err invalid value of G, length of channel L0 (G[2]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void CylindricalFriction::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);
	
	if ((G[0] != rou_)|| (G[1] != D0_)|| (G[2] != L_))
	{
		rou_ = G[0];
		D0_ = G[1];
		L_ = G[2];
		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void CylindricalFriction::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		L_,
		A_
	};
}

HSReal CylindricalFriction::getLength()
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

void CylindricalFriction::setLength(const HSReal L)
{
	L_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
