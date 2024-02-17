#include <pch.h>
#include <HydraulicResistances/SharpUnexpectedSizeChange.h>
#include <math/mathlib.h>

void SharpUnexpectedSizeChange::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
	}
}

void SharpUnexpectedSizeChange::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (G.size() < 3)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 3 in the element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (flagHandleWarnings)
	{
		if (G.size() > 3)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 3 in the element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G[0] < 0.0)
	{
		std::cerr << "%err invalid value of G, roughness rou (G[0]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] <= 0.0)
	{
		std::cerr << "%err invalid value of G, diameter 1 D0 (G[1]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[2] <= 0.0)
	{
		std::cerr << "%err invalid value of G, diameter 2 D1 (G[2]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void SharpUnexpectedSizeChange::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	// chek values
	errorHandling();

	A_ = M_PI * pow(0.5 * D0_, 2.0);
	A2_ = M_PI * pow(0.5 * max(D1_, D2_), 2.0);
	relRou_ = rou_ / D0_;

	CSIlf_ = 0.0;
	lf_ = 0.0;

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
		// inverse element for negative flow
		if (Re < 0.0)
		{
			Re = abs(Re);

			// diagram 4-1
			if (D1_ > D2_)
			{
				diagram_ = "4-1";
				if (Re >= 3.3e3)
				{
					CSIlr_ = pow(1.0 - (A2_ / A_), 2.0);
				}
				if ((Re < 3.3e3) && (Re >= 500.0))
				{
					CSIlr_ = -8.44556 - 26.163 * pow(1.0 - (A2_ / A_), 2.0) - 5.38086 * pow(1.0 - (A2_ / A_), 4.0)
						+ log(Re) * (6.007 + 18.5372 * pow(1.0 - (A2_ / A_), 2.0) + 3.9978 * pow(1.0 - (A2_ / A_), 4.0))
						+ pow(log(Re), 2.0) * (-1.02318 - 3.0916 * pow(1.0 - (A2_ / A_), 2.0) - 0.680943 * pow(1.0 - (A2_ / A_), 4.0));
				}
				if ((Re < 500.0) && (Re >= 10.0))
				{
					CSIlr_ = 3.62536 + 10.744 * pow(1.0 - (A2_ / A_), 2.0) - 4.41041 * pow(1.0 - (A2_ / A_), 4.0)
						+ (1.0 / log(Re)) * (-18.13 - 56.77855 * pow(1.0 - (A2_ / A_), 2.0) + 33.40344 * pow(1.0 - (A2_ / A_), 4.0))
						+ (1.0 / pow(log(Re), 2.0)) * (30.8558 + 99.9542 * pow(1.0 - (A2_ / A_), 2.0) - 62.78 * pow(1.0 - (A2_ / A_), 4.0))
						+ (1.0 / pow(log(Re), 3.0)) * (-13.217 - 53.9555 * pow(1.0 - (A2_ / A_), 2.0) - 33.8053 * pow(1.0 - (A2_ / A_), 4.0));
				}
				if (Re < 10.0)
				{
					CSIlr_ = 30.0 / Re;
				}
			}
			// diagram 4-9
			else
			{
				diagram_ = "4-9";

				if (flagHandleWarnings)
				{
					// check Re for diagram 4-9
					if (Re < 1.e4)
					{
						std::cerr << "%warn Re = " << Re << " less than 1e4 in the element " << id_ << " (" << name_ << ") (diagram 4-9)\n";
					}
				}
				CSIlr_ = 0.5 * pow(1.0 - (A_ / A2_), 0.75);
			}
		}
		// for positive flow
		else
		{
			// diagram 4-1
			if (D1_ < D2_)
			{
				diagram_ = "4-1";
				if (Re >= 3.3e3)
				{
					CSIlr_ = pow(1.0 - (A_ / A2_), 2.0);
				}
				if ((Re < 3.3e3) && (Re >= 500.0))
				{
					CSIlr_ = -8.44556 - 26.163 * pow(1.0 - (A_ / A2_), 2.0) - 5.38086 * pow(1.0 - (A_ / A2_), 4.0)
						+ log(Re) * (6.007 + 18.5372 * pow(1.0 - (A_ / A2_), 2.0) + 3.9978 * pow(1.0 - (A_ / A2_), 4.0))
						+ pow(log(Re), 2.0) * (-1.02318 - 3.0916 * pow(1.0 - (A_ / A2_), 2.0) - 0.680943 * pow(1.0 - (A_ / A2_), 4.0));
				}
				if ((Re < 500.0) && (Re >= 10.0))
				{
					CSIlr_ = 3.62536 + 10.744 * pow(1.0 - (A_ / A2_), 2.0) - 4.41041 * pow(1.0 - (A_ / A2_), 4.0)
						+ (1.0 / log(Re)) * (-18.13 - 56.77855 * pow(1.0 - (A_ / A2_), 2.0) + 33.40344 * pow(1.0 - (A_ / A2_), 4.0))
						+ (1.0 / pow(log(Re), 2.0)) * (30.8558 + 99.9542 * pow(1.0 - (A_ / A2_), 2.0) - 62.78 * pow(1.0 - (A_ / A2_), 4.0))
						+ (1.0 / pow(log(Re), 3.0)) * (-13.217 - 53.9555 * pow(1.0 - (A_ / A2_), 2.0) - 33.8053 * pow(1.0 - (A_ / A2_), 4.0));
				}
				if (Re < 10.0)
				{
					CSIlr_ = 30.0 / Re;
				}
			}
			// diagram 4-9
			else
			{
				diagram_ = "4-9";

				if (flagHandleWarnings)
				{
					// check Re for diagram 4-9
					if (Re < 1.e4)
					{
						std::cerr << "%warn Re = " << Re << " less than 1e4 in the element " << id_ << " (" << name_ << ") (diagram 4-9)\n";
					}
				}
				CSIlr_ = 0.5 * pow(1.0 - (A_ / A2_), 0.75);
			}
		}
		CSI_ = CSIlr_ + CSIlf_;
	}

	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* SharpUnexpectedSizeChange::copy() const
{
	return new SharpUnexpectedSizeChange(name_, Re_,
		{
			rou_,
			D0_,
			D1_
		}
	);
}

void SharpUnexpectedSizeChange::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != D1_))
	{
		rou_ = G[0];
		D0_ = G[1];
		D1_ = G[2];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void SharpUnexpectedSizeChange::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		D1_,
		A_,
		A2_
	};
}

HSReal SharpUnexpectedSizeChange::getLength()
{
	return 1.e-6;
}

void SharpUnexpectedSizeChange::setLength(const HSReal L)
{
	return void();
}
